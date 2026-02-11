getTrainingIdFromValue (int n)
{
  int z = 0;
  if (n == z ++) return MISSION_TUTORIAL;
  else if (n == z ++) return MISSION_TUTORIAL2;
  else if (n == z ++) return MISSION_DOGFIGHT;
  else if (n == z ++) return MISSION_TUTORIAL3;
  else if (n == z ++) return MISSION_FREEFLIGHT1;
  else if (n == z ++) return MISSION_DEATHMATCH1;
  else if (n == z ++) return MISSION_DEATHMATCH2;
  else if (n == z ++) return MISSION_DEATHMATCH3;
  else if (n == z ++) return MISSION_TEAMBASE1;
  else if (n == z ++) return MISSION_WAVES1;
  else
  {
    return MISSION_CUSTOM1 + n - 10;
  }
  return 0;
}
