resolve(
	ArResolver::ActionMap *actions, ArRobot *robot, bool logActions)
{
  ArResolver::ActionMap::reverse_iterator it;
  ArAction *action;
  ArActionDesired *act;
  ArActionDesired averaging;
  bool first = true;
  int lastPriority;
  bool printedFirst = true;
  int printedLast;

  if (actions == NULL)
    return NULL;

  myActionDesired.reset();
  averaging.reset();
  averaging.startAverage();
  for (it = actions->rbegin(); it != actions->rend(); ++it)
  {
    action = (*it).second;
    if (action != NULL && action->isActive())
    {

      if (first || (*it).first != lastPriority)
      {
	averaging.endAverage();
	myActionDesired.merge(&averaging);

	averaging.reset();
	averaging.startAverage();
	first = false;
	lastPriority = (*it).first;
      }
      act = action->fire(myActionDesired);
      if (robot != NULL && act != NULL)
	act->accountForRobotHeading(robot->getTh());
      if (act != NULL)
	act->sanityCheck(action->getName());

      averaging.addAverage(act);
      if (logActions && act != NULL && act->isAnythingDesired())
      {
	if (printedFirst || printedLast != (*it).first)
	{
	  ArLog::log(ArLog::Terse, "Priority %d:", (*it).first);
	  printedLast = (*it).first;
	  printedFirst = false;
	}
	ArLog::log(ArLog::Terse, "Action: %s", action->getName());
	act->log();
      }


    }
  }
  averaging.endAverage();
  myActionDesired.merge(&averaging);


  return &myActionDesired;
}
