checkParameterArgumentString(
	const char *argument, const char **dest, bool *wasReallySet,
	bool returnFirst)
{
  char *param;
  param = checkParameterArgument(argument, returnFirst);

  if (param == NULL)
  {
    if (wasReallySet && !myReallySetOnlyTrue)
      *wasReallySet = false;
    return true;
  }
  else if (param[0] != '\0')
  {
    *dest = param;
    if (wasReallySet)
      *wasReallySet = true;
    return true;
  }
  else
  {
    ArLog::log(ArLog::Normal, "No argument given to %s", argument);
    return false;
  }
}
