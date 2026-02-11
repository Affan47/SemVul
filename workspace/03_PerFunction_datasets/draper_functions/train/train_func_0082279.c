activate(void)
{
  if (!baseActivate())
    return;
  addKeyHandler('1', &myAllSonarCB);
  addKeyHandler('2', &myFirstSonarCB);
  addKeyHandler('3', &mySecondSonarCB);
  addKeyHandler('4', &myThirdSonarCB);
  addKeyHandler('5', &myFourthSonarCB);
}
