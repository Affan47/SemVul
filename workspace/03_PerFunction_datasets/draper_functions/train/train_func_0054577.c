Get_Bullet_Data ( char* DataPointer )
{
  char *BulletPointer;
  char *EndOfBulletData;
  int i, size;
  int BulletIndex=0;

  float bullet_speed_calibrator;
  float bullet_damage_calibrator;

#define BULLET_SECTION_BEGIN_STRING "*** Start of Bullet Data Section: ***"
#define BULLET_SECTION_END_STRING "*** End of Bullet Data Section: ***"
#define NEW_BULLET_TYPE_BEGIN_STRING "** Start of new bullet specification subsection **"

#define BULLET_RECHARGE_TIME_BEGIN_STRING "Time is takes to recharge this bullet/weapon in seconds :"
#define BULLET_SPEED_BEGIN_STRING "Flying speed of this bullet type :"
#define BULLET_DAMAGE_BEGIN_STRING "Damage cause by a hit of this bullet type :"

#define BULLET_ONE_SHOT_ONLY_AT_A_TIME "Cannot fire until previous bullet has been deleted : "
#define BULLET_BLAST_TYPE_CAUSED_BEGIN_STRING "Type of blast this bullet causes when crashing e.g. against a wall :"

#define BULLET_SPEED_CALIBRATOR_STRING "Common factor for all bullet's speed values: "
#define BULLET_DAMAGE_CALIBRATOR_STRING "Common factor for all bullet's damage values: "

  BulletPointer = LocateStringInData ( DataPointer , BULLET_SECTION_BEGIN_STRING );
  EndOfBulletData = LocateStringInData ( DataPointer , BULLET_SECTION_END_STRING );

  DebugPrintf (2, "\n\nStarting to read bullet data...\n\n");


  Number_Of_Bullet_Types = CountStringOccurences ( DataPointer , NEW_BULLET_TYPE_BEGIN_STRING ) ;


  if ( Bulletmap == NULL )
    {
      size = sizeof(bulletspec);
      Bulletmap = MyMalloc ( size * (Number_Of_Bullet_Types + 1) + 1 );
      DebugPrintf (1, "\nWe have counted %d different bullet types in the game data file." ,
		   Number_Of_Bullet_Types );
      DebugPrintf (1, "\nMEMORY HAS BEEN ALLOCATED.\nTHE READING CAN BEGIN.\n" );

    }


  BulletPointer=DataPointer;

  while ( (BulletPointer = strstr ( BulletPointer, NEW_BULLET_TYPE_BEGIN_STRING )) != NULL)
    {
      DebugPrintf (1, "\n\nFound another Bullet specification entry!  Lets add that to the others!");
      BulletPointer ++;


      ReadValueFromString( BulletPointer ,  BULLET_RECHARGE_TIME_BEGIN_STRING , "%f" ,
			   &Bulletmap[BulletIndex].recharging_time);


      ReadValueFromString( BulletPointer ,  BULLET_SPEED_BEGIN_STRING , "%f" ,
			   &Bulletmap[BulletIndex].speed);


      ReadValueFromString( BulletPointer ,  BULLET_DAMAGE_BEGIN_STRING , "%d" ,
			   &Bulletmap[BulletIndex].damage);


      ReadValueFromString( BulletPointer ,  BULLET_BLAST_TYPE_CAUSED_BEGIN_STRING , "%d" ,
			   &Bulletmap[BulletIndex].blast);

      BulletIndex++;
    }


  DebugPrintf (1, "\n\nStarting to read bullet calibration section\n\n");


  ReadValueFromString( DataPointer ,  BULLET_SPEED_CALIBRATOR_STRING , "%f" ,
		       &bullet_speed_calibrator);


  ReadValueFromString( DataPointer ,  BULLET_DAMAGE_CALIBRATOR_STRING , "%f" ,
		       &bullet_damage_calibrator);


  for ( i = 0 ; i < Number_Of_Bullet_Types ; i++ )
    {
      Bulletmap[i].speed *= bullet_speed_calibrator;
      Bulletmap[i].damage *= bullet_damage_calibrator;
    }

  DebugPrintf (1, "\nEnd of Get_Bullet_Data ( char* DataPointer ) reached.");
}
