checkKeys(void)
{
  int key;
  std::map<int, ArFunctor *>::iterator it;

  if (myRestored)
    return;


  while (!myRestored && (key = getKey()) != -1)
  {

    if ((it = myMap.find(key)) != myMap.end())
    {

      it->second->invoke();
    }
  }
}
