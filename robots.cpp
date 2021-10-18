#include <iostream>
#include <vector>

using std::vector;
class Robots{

    private:
    int x_,y_;
    char heading_;

    public:
    Robots(int x, int y, char head):x_(x),y_(y),heading_(head){};

    int moveForward(){
        if (heading_=='n')
        { y_ = y_+1; }
        else if (heading_=='s')
        { y_ = y_-1; }
        else if (heading_ == 'e')
        { x_ = x_ +1; }
        else 
        {x_ = x_ -1;}
        
        return 0;
    }
    int moveBackward(){
        if (heading_=='n')
        { y_ = y_-1; }
        else if (heading_=='s')
        { y_ = y_+1; }
        else if (heading_ == 'e')
        { x_ = x_ -1; }
        else 
        {x_ = x_ +1;}

        return 0;
    }

    int turnLeft(){
        if (heading_=='n')
        { heading_ = 'w'; }
        else if (heading_=='s')
        { heading_ = 'e'; }
        else if (heading_ == 'w')
        { heading_ = 's'; }
        else 
        {heading_ = 'n';}
        return 0;
    }
    int turnRight(){
        if (heading_=='n')
        { heading_ = 'e'; }
        else if (heading_=='s')
        { heading_ = 'w'; }
        else if (heading_ == 'w')
        { heading_ = 'n'; }
        else 
        {heading_ = 's';}        
        return 0;
    }

    int getX(){return x_;};
    int getY(){return y_;};
    char getHead(){return heading_;};
};

char* generatefield(char* gamefield,int X_field, int Y_field){

    for (int i = 0; i < Y_field; i++)
    {
        for (int j = 0; j < X_field; j++)
        {
            *(gamefield + i*X_field +j ) = '.';
        }
        
    }
    return gamefield;
};

void printfield(char* gamefield, int X_field, int Y_field){
    for (int i = 0; i <  Y_field; i++)
    {
        for (int j = 0; j < X_field; j++)
        {
            std::cout << *(gamefield+i*X_field+j);
        }
        std::cout<<""<<std::endl;
    }
};

int playcondition(Robots HumanRobo, int X_field, int Y_field){

    int contPlaying = (0 < HumanRobo.getX() && HumanRobo.getX() < X_field) && (0 < HumanRobo.getY() && HumanRobo.getY() < Y_field);
    return contPlaying;
};

int collisioncondition(Robots HumanRobo, vector<Robots> ObjRobos,int n){
    int sumClash{0};
    for (int i = 0; i < n; i++)
    {
        if((HumanRobo.getX() == ObjRobos[i].getX()) && (HumanRobo.getY() == ObjRobos[i].getY())){
        break;
        }
        sumClash = sumClash + 1;
    }
    
    int humanIsSafe = sumClash == n;

    return humanIsSafe;

};

int main(){
    int n{2}, Xh,Yh;
    int X_field = 22,Y_field=14;//dimension of the game field
    char PSIh;
    int fillrobotpos[n][2];
    char fillrobothead[n][1];
    vector<Robots> ObjRobos;

    std::cout << "Welcome to Robot vs Human Game. In a 22 x 14 grid, robots will try to chase the human bot. Human bot needs to reach the boundary of the field without being caught!" << std::endl;
    std::cout << " -------- ------- --------- " << std::endl;
    std::cout << "Rules of the Game: " << std::endl;
    std::cout << "Choose the number of robots and enter their starting 'x' & 'y' position in 22 x 14 grid, and heading direction from 'n s e w'. " << std::endl;
    std::cout << "Likewise, choose the Human bot's starting 'x' & 'y' position in 22 x 14 grid, and heading direction from 'n s e w'." << std::endl;
    std::cout << " " << std::endl;
    std::cout << "You can move the Human bot using input command from 'f=forward','b=back','l=left','r=right' " << std::endl;
    std::cout << " -------- ------- --------- " << std::endl;
    std::cout << "Get Set Go!! " << std::endl;
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Enter the number of robots" << std::endl;
    std::cin >> n;

    //taking robots data from user
    for (int i = 1; i <= n; i++) 
    {
            std::cout << "Enter the x position of Robot " << i <<std::endl;
            std::cin >> fillrobotpos[i-1][0];
            std::cout << "Enter the y position of Robot " << i <<std::endl;
            std::cin >> fillrobotpos[i-1][1];
            std::cout << "Enter the heading of Robot "<< i << " in 'n s e w'"<<std::endl;
            std::cin >> fillrobothead[i-1][0];

            //create robot object
            ObjRobos.push_back(Robots(fillrobotpos[i-1][0],fillrobotpos[i-1][1],fillrobothead[i-1][0])); //create robot objects
    }

    //taking human robot data from user
    std::cout << "Enter the x position of the human robot" <<std::endl;
    std::cin >> Xh;
    std::cout << "Enter the y position of the human robot" <<std::endl;
    std::cin >> Yh;
    std::cout << "Enter the heading of the human robot in 'n s e w'" <<std::endl;
    std::cin >> PSIh;
    
    //create human robot object
    Robots HumanRobo(Xh,Yh,PSIh);


    //text print all robot data as entered by user
    for (int i = 0; i < n; i++) 
    {
        std::cout << "Robot "<< i+1  << " x position: " << ObjRobos[i].getX();
        std::cout << " y position: " << ObjRobos[i].getY();
        std::cout << " heading: "    << ObjRobos[i].getHead() << std::endl;
    }
    
    std::cout << "Human Robot "  << " x position: " << HumanRobo.getX();
    std::cout << " y position: " << HumanRobo.getY();
    std::cout << " heading: "    << HumanRobo.getHead() << std::endl;
 
    //generate the game field
    char gamefield[Y_field][X_field];
    generatefield((char*)gamefield, X_field, Y_field);

    //add human robot to the grid
    gamefield[Y_field - HumanRobo.getY()][HumanRobo.getX()-1] = 'H';
    
    //add robot to the grid
    for (int k = 0; k < n; k++)
    {
        gamefield[ Y_field - (ObjRobos[k].getY()) ][ (ObjRobos[k].getX() - 1) ] = 'R';
    }
    
    // print the field with robots
    printfield((char*)gamefield,X_field,Y_field);


    //game loop
    while(playcondition(HumanRobo,X_field,Y_field) && collisioncondition(HumanRobo,ObjRobos,n)){

        char moveInput;
        std::cout << "Enter input command from 'f=forward','b=back','l=left','r=right' for human robot: " << std::endl;
        std::cin >> moveInput;

        switch(moveInput){
            case 'f':
                HumanRobo.moveForward();
                break;
            case 'b':
                HumanRobo.moveBackward();
                break;
            case 'l':
                HumanRobo.turnLeft();
                break;
            case 'r':
                HumanRobo.turnRight();
                break;
        }

        //now the robots make a move{}
        for (int i = 0; i < n; i++)
        {
            if ((std::abs(HumanRobo.getX()-ObjRobos[i].getX()) >  std::abs(HumanRobo.getY()-ObjRobos[i].getY())))// && std::abs(HumanRobo.getX()-ObjRobos[i].getX()) >0)//travel in x
            {
                if ((HumanRobo.getX()-ObjRobos[i].getX()) > 0 ) // travel in positive x direction
                {
                    if (ObjRobos[i].getHead() =='n')
                    { ObjRobos[i].turnRight();}
                    else if (ObjRobos[i].getHead() =='s')
                    {ObjRobos[i].turnLeft();}
                    else if (ObjRobos[i].getHead() =='w')
                    {ObjRobos[i].moveBackward();}
                    else if (ObjRobos[i].getHead() =='e')
                    {ObjRobos[i].moveForward();}                
                }
                else if ((HumanRobo.getX()-ObjRobos[i].getX()) < 0 ) // travel in negative x direction
                {
                    if (ObjRobos[i].getHead() =='n')
                    { ObjRobos[i].turnLeft();}
                    else if (ObjRobos[i].getHead() =='s')
                    {ObjRobos[i].turnRight();}
                    else if (ObjRobos[i].getHead() =='w')
                    {ObjRobos[i].moveForward();}
                    else if (ObjRobos[i].getHead() =='e')
                    {ObjRobos[i].moveBackward();}                
                }
            }
            else //travel in y
            {
                if ((HumanRobo.getY()-ObjRobos[i].getY()) > 0 ) //travel down
                {
                    if (ObjRobos[i].getHead() =='n')
                    { ObjRobos[i].moveForward();}
                    else if (ObjRobos[i].getHead() =='s')
                    {ObjRobos[i].moveBackward();}
                    else if (ObjRobos[i].getHead() =='w')
                    {ObjRobos[i].turnLeft();}
                    else if (ObjRobos[i].getHead() =='e')
                    {ObjRobos[i].turnRight();}                
                }
                else if ((HumanRobo.getY()-ObjRobos[i].getY()) < 0 ) // travel up
                {
                    if (ObjRobos[i].getHead() =='n')
                    { ObjRobos[i].moveBackward();}
                    else if (ObjRobos[i].getHead() =='s')
                    {ObjRobos[i].moveForward();}
                    else if (ObjRobos[i].getHead() =='w')
                    {ObjRobos[i].turnRight();}
                    else if (ObjRobos[i].getHead() =='e')
                    {ObjRobos[i].turnLeft();}                
                }
            }
            
        }
        


        generatefield((char*)gamefield, X_field, Y_field);


        gamefield[Y_field - HumanRobo.getY()][HumanRobo.getX()-1] = 'H';
    
        for (int k = 0; k < n; k++)
        {
            gamefield[ Y_field - (ObjRobos[k].getY()) ][ (ObjRobos[k].getX() - 1) ] = 'R';
        }

        printfield((char*)gamefield,X_field,Y_field);

    }

    if(!playcondition(HumanRobo,X_field,Y_field)){
        std::cout << "You Win!" << std::endl;
    }
    else if(!collisioncondition(HumanRobo,ObjRobos,n)){
        std::cout << "You Loose!" << std::endl;
    }
    
    return 0;
}