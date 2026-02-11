madeConnection(void)
{
  std::list<ArFunctor *>::iterator it;

  myLastReading.setToNow();
  for (it = myConnectCBList.begin(); it != myConnectCBList.end(); it++)
    (*it)->invoke();
}
