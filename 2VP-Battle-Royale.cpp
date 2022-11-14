/****************************************************************************************************

Battle Royale is a 2P Gattle Game

Players:
Ogre    : High Health, Low Damage, Low Healing
Samurai : Avg Health, Avg Damage, Avg Healing
Ninja   : Low Health, High Damage, Avg Healing

Parameter         : High,Average,Low
Health            : 500, 350, 250
Base Damage       : 70, 55, 45
Additional Damage : 20-35, 15-30 ,10-25
Healing           : NA,  55-75, 35-55

Special Ability  - Special Abilities Loaded on every fifth move but will be used only if player chooses to Attack.
Ogre : Rock Smash - A deadly damage of 150 damage points.
Samurai : Focus Stun - enemy gets stunned and will end up wasting their 3 moves.
Ninja: Shadow Clone - creates a shadow clone of 150 hp. Ninja will only get attacked after shadow clone dies.

****************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

class Player{

  protected:

  int health;
  int fullhealth;
  int baseDamage;
  int adDamage;
  int heal;
  int maxDamage,minDamage,maxHeal,minHeal;
  int moveCount;
  char name,opp;
  
  public:
  
  Player(){
    //cout<<"Player"<<health<<endl;
  }
  virtual int giveDamage(){
    return 0;
  }
  virtual int takeDamage(int dmg){
    return 0;
  }
  virtual void Heal(){
  }
  int getHealth(){
    return health;
  }
};

class Ogre : public Player {

  int stun = 0, stunCount = 0;
  public:

  Ogre(char _name){
    health = 500;
    fullhealth = 500;
    baseDamage = 45;
    maxDamage = 25;
    minDamage = 10;
    maxHeal = 55;
    minHeal = 35;
    name = _name;
    moveCount = 0;
    opp = (name == '1')? '2' : '1';

    cout<<"\nPlayer "<<name<<" is Ogre of Health "<<fullhealth<<" and Special Ability Rock Smash !!\n";
  }

  int giveDamage(){
    int Damage;

    //Check whether player got stunned. If yes, skip attacking
    if (stun == 1 && stunCount < 3){
      cout<<"Player "<<name<<" is stunned. Won't be able to attack...\n";
      stunCount++;
      return 0;
    }
    //Special Ability
    if (moveCount >= 4) {
      moveCount = 0;
      cout<<"Player "<<name<<" used Ogre special ability: Rock Smash !!!\n";
      cout<<"Player "<<name<<" gave a deadly blow of 150 damage\n";
      return 150;
    }
    //Normal Attack
    moveCount++;
    srand(time(0));
    Damage = baseDamage + (rand() % (maxDamage + 1 - minDamage) + minDamage);
    cout<<"Player "<<name<<" attacked with "<<Damage<<" damage\n";
    return Damage;
  }

  int takeDamage(int dmg){
    //Skip the damage 999 which denotes stun.
    if (dmg == 999){
      stun = 1;
      stunCount = 0;
      return 200;
    }
    //skipping 0 condition.
    if (dmg == 0){return 200;}
    
    health -= dmg;
    if (health <= 0){
      cout<<"Oh no ... Player "<<name<<" died"<<'\n';
      cout<<"Player "<<opp<<" Won the game\n";
      return 405;
      }
    else{
      cout<<"Player "<<name<<" health after getting attacked is: "<<health<<'\n';
    }
    return 200;
  }

  void Heal(){
    moveCount++;
    srand(time(0));
    int randomHeal = (rand() % (maxHeal + 1 - minHeal) + minHeal);
    if (health == fullhealth){
      cout<<"Player "<<name<<" Health is already full. Heal is not applied.\n";
      return;
    }
    health += randomHeal; // Healing
    if (health >= fullhealth) {health = fullhealth;}
    cout<<"Player "<<name<<" healed with "<<randomHeal<<" hp points\n";
    cout<<"Player "<<name<<" health after healing is "<<health<<'\n';
  }
};

class Samurai : public Player {
  int stun = 0, stunCount = 0;
  public:

  Samurai(char _name){
    health = 350;
    fullhealth = 350;
    baseDamage = 55;
    maxDamage = 30;
    minDamage = 15;
    maxHeal = 75;
    minHeal = 55;
    name = _name;
    moveCount = 0;
    opp = (name == '1')? '2' : '1';

    cout<<"\nPlayer "<<name<<" is Samurai of Health "<<fullhealth<<" and Special Ability Focus Stun !!\n";
  }

  int giveDamage(){
    //Check whether player got stunned. If yes, skip attacking
    if (stun == 1 && stunCount <= 3){
      cout<<"Player "<<name<<" is stunned. Won't be able to attack...\n";
      stunCount++;
      return 0;
    }
    
    int Damage;
    //Special Ability
    if (moveCount >= 4) {
      moveCount = 0;
      cout<<"Player "<<name<<" used Samurai special ability: Focus Stun !!!\n";
      cout<<"Player "<<opp<<" got Stunned!\n";
      return 999; //code number to identify stun attack
    }
    //Normal Attack
    moveCount++;
    srand(time(0));
    Damage = baseDamage + (rand() % (maxDamage + 1 - minDamage) + minDamage);
    cout<<"Player "<<name<<" attacked with "<<Damage<<" damage\n";
    return Damage;
  }

  int takeDamage(int dmg){
    
    //Skip the damage 999 which denotes stun.
    if (dmg == 999){
      stun = 1;
      stunCount = 0;
      return 200;
    }
    
    //skipping 0 condition.
    if (dmg == 0){return 200;}
    
    health -= dmg;
    if (health <= 0){
      cout<<"Oh no ... Player "<<name<<" died"<<'\n';
      cout<<"Player "<<opp<<" Won the game\n";
      return 405;
      }
    else{
      cout<<"Player "<<name<<" health after getting attacked is: "<<health<<'\n';
    }
    return 200;
  }

  void Heal(){
    moveCount++;
    srand(time(0));
    int randomHeal = (rand() % (maxHeal + 1 - minHeal) + minHeal);
    if (health == fullhealth){
      cout<<"Player "<<name<<" Health is already full. Heal is not applied.\n";
      return;
    }
    health += randomHeal; // Healing
    if (health >= fullhealth) {health = fullhealth;}
    cout<<"Player "<<name<<" healed with "<<randomHeal<<" hp points\n";
    cout<<"Player "<<name<<" health after healing is "<<health<<'\n';
  }
};

class Ninja : public Player{
  int stun = 0, stunCount = 0;
  int shadowClone = 0;
  public:

  Ninja(char _name){
    health = 250;
    fullhealth = 250;
    baseDamage = 70;
    maxDamage = 35;
    minDamage = 20;
    maxHeal = 75;
    minHeal = 55;
    name = _name;
    moveCount = 0;
    opp = (name == '1')? '2' : '1'; 

    cout<<"\nPlayer "<<name<<" is Ninja of Health "<<fullhealth<<" and Special Ability Shadow Clone !!\n";
  }

  int giveDamage(){
    //Check whether player got stunned. If yes, skip attacking
    if (stun == 1 && stunCount <= 3){
      cout<<"Player "<<name<<" is stunned. Won't be able to attack...\n";
      stunCount++;
      return 0;
    }
    
    int Damage;
    //Special Ability
    if (moveCount >= 4) {
      moveCount = 0;
      cout<<"Player "<<name<<" used Ninja special ability: Shadow Clone !!!\n";
      cout<<"Player "<<name<<" Summoned a shadow clone of 150 HP\n";
      shadowClone = 150;
      return 0;
    }
    //Normal Attack
    moveCount++;
    srand(time(0));
    Damage = baseDamage + (rand() % (maxDamage + 1 - minDamage) + minDamage);
    cout<<"Player "<<name<<" attacked with "<<Damage<<" damage\n";
    return Damage;
  }

  int takeDamage(int dmg){
    
    //Skip the damage 999 which denotes stun.
    if (dmg == 999){
      stun = 1;
      stunCount = 0;
      return 200;
    }
    //skipping 0 condition.
    if (dmg == 0){return 200;}

    //killing shadowClone first
    if (shadowClone > 0){
      shadowClone -= dmg;
      if (shadowClone <= 0){
        cout<<"Shadow Clone of Player "<<name<<" Died\n";
        shadowClone = 0;
      }
      cout<<"Shadow Clone's health after getting attacked is: "<<shadowClone<<" out of 150\n";
      return 200;
    }
    //normal takeDamage
    health -= dmg;
    if (health <= 0){
      cout<<"Oh no ... Player "<<name<<" died"<<'\n';
      cout<<"Player "<<opp<<" Won the game\n";
      return 405;
      }
    else{
      cout<<"Player "<<name<<" health after getting attacked is: "<<health<<'\n';
    }
    return 200;
  }

  void Heal(){
    moveCount++;
    srand(time(0));
    int randomHeal = (rand() % (maxHeal + 1 - minHeal) + minHeal);
    if (health == fullhealth){
      cout<<"Player "<<name<<" Health is already full. Heal is not applied.\n";
      return;
    }
    health += randomHeal; // Healing
    if (health >= fullhealth) {health = fullhealth;}
    cout<<"Player "<<name<<" healed with "<<randomHeal<<" hp points\n";
    cout<<"Player "<<name<<" health after healing is "<<health<<'\n';
  }
};


void gameTitle(){
  //GAME NAME printing
  system("clear");
  cout<<'*'<<setfill('*')<<setw(101)<<'*'<<endl;
  cout<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<<endl;
  cout<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<<endl;
  cout<<'*'<<setfill(' ')<<std::string(40, ' ' )<<setw(60)<<left<<"Battle Royale"<<'*'<<endl;
  cout<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<<endl;
  cout<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<<endl;
  cout<<'*'<<setfill('*')<<setw(101)<<'*'<<endl;
  //--------------------------------------------------------------------------------------------
}

void Instructions(){
  cout<<"\n\nThis is a 2 Player vs Player Battle Game\n\n";
  cout<<"Players in the game can Attack or Heal\n\n";
  cout<<"Special ability gets loaded for every fifth move and gets released automatically when player chooses to attack.\n\n";
  cout<<"Characters in the game\n\n";
  cout<<"Ogre : A giant humanoid with high health.\nUses a special ability Rock Smash that deals 150 damage to the enemy.\n\n";
  cout<<"Samurai : A focussed and discliplined warrior.\nUses a special ability Focus Stun to stun his opponents for duration of 3 moves\n\n";
  cout<<"Ninja : A trained assassin with fast and high damage ability.\nUses a special ability Shadow Clone that summons a Shadow Clone of 150 HP.\nEnemy must kill the clone first to attack the player.\n\n";
}

// This Function Makes the move (Attack or Heal)
int PlayerMove(Player *X,Player *Y){
  char move;
  int death;
  int heal;
  Start:
  cout<<"Press A to Attack OR Press H to Heal:\n";
  cin>>move;
  cout<<endl;
  if(move == 'A' || move == 'a'){
    death = Y->takeDamage(X->giveDamage());
    return death;
  } 
  else if(move == 'H' || move == 'h'){
    X->Heal();
    return 0;
  }
  else{
    cout<<"Invalid Input ..\n\n";
    goto Start;
  } 
}

void gameLoop(Player *A, Player *B){
  do{
  int move;
  //Player 1 make his move
  cout<<"\nPlayer 1 make your move !"<<'\n';
  move = PlayerMove(A,B);
  if (move == 405){break;} //Death Break
    
  //Player 2 make his move
  cout<<"\nPlayer 2 make your move !"<<'\n';
  move = PlayerMove(B,A);
  if (move == 405){break;} // Death Break
    
  cout<<'-'<<setfill('-')<<setw(101)<<'-'<<endl;
  }while(A->getHealth()>0 && B->getHealth()>0);
}

int main(){
  
  gameTitle();
  Instructions();

  char userInput;
  do {
    cout<<endl<<"Press S to start the game or any other key to exit..."<<endl;
    cin>>userInput;
    if ((userInput == 'S')||(userInput == 's'))
    {
      cout<<'+'<<setfill('+')<<setw(101)<<'+'<<endl;
      
      //Player Selection Happens Here ------------------
      char playerA,playerB;
      Player *A , *B;
      p1: //Player 1 selection location
      cout<<"\nPlayer 1 : Select your character \n";
      cout<<"1: Ogre\n"<<"2: Samurai\n"<<"3: Ninja\n";
      cin>>playerA;
      switch(playerA)
        {
          case '1': A = new Ogre('1');
                    break;
          case '2': A = new Samurai('1');
                    break;
          case '3': A = new Ninja('1');
                    break;
          default: cout<<"Invalid Input\n";
                    goto p1;
        }
      p2: //Player 2 selection location
      cout<<"\nPlayer 2 : Select your character \n";
      cout<<"1: Ogre\n"<<"2: Samurai\n"<<"3: Ninja\n";
      cin>>playerB;
      switch(playerB)
        {
          case '1': B = new Ogre('2');
                    break;
          case '2': B = new Samurai('2');
                    break;
          case '3': B = new Ninja('2');
                    break;
          default: cout<<"Invalid Input\n";
                    goto p2;
        }
      cout<<'+'<<setfill('+')<<setw(101)<<'+'<<endl;
      
      //BATTLE Loop Starts Here -----------------
      gameLoop(A,B);

      delete A;
      delete B;
    }
    else
    {
      cout<<"Thanks for playing !!!"<<endl;
    }
  }while((userInput == 'S')||(userInput == 's'));
  
  return 0;
}













