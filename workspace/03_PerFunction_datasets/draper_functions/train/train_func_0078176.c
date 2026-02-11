removeAllSashes(void)
{
  sashAction(MSTrue);
  for (unsigned i=0;i<sashList().length();i++) delete _sashList(i);
  sashList().removeAll();
  sashAction(MSFalse);
}
