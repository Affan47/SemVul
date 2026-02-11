deactivateActions(void)
{
  ArResolver::ActionMap *am;
  ArResolver::ActionMap::iterator amit;

  am = getActionMap();
  if (am == NULL)
  {
    ArLog::log(ArLog::Terse,
            "ArRobot::deactivateActions: NULL action map... failed.");
    return;
  }
  for (amit = am->begin(); amit != am->end(); amit++)
    (*amit).second->deactivate();


}
