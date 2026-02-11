enableSonar()
{
  mySonarEnabled = true;
  myAutonomousDrivingSonarEnabled = false;
  comInt(ArCommands::SONAR, 1);

  int ii;
  for (ii = 1; ii <= Aria::getMaxNumSonarBoards(); ii++)
  {
    ArSonarMTX *sonarMTX = findSonar(ii);

    if (sonarMTX == NULL)
      continue;

    sonarMTX->turnOnTransducers();
  }
}
