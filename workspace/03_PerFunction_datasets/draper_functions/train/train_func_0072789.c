remAction(ArAction *action)
{
  ArResolver::ActionMap::iterator it;
  ArAction *act;

  for (it = myActions.begin(); it != myActions.end(); ++it)
  {
    act = (*it).second;
    if (act == action)
      break;
  }
  if (it != myActions.end())
  {
    myActions.erase(it);
    return true;
  }
  return false;

}
