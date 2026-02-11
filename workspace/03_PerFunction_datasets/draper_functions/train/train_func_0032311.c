checkParameterArgumentFloat(
	char *argument, float *dest, bool *wasReallySet, bool returnFirst)
{
  char *param = checkParameterArgument(argument, returnFirst);
  if (param == NULL)
  {
    if (wasReallySet) *wasReallySet = false;
    return true;
  }
  else if (param[0] != '\0')
  {
    char *endPtr;
    float floatVal = strtod(param, &endPtr);
    if(endPtr == param)
    {
      ArLog::log(ArLog::Normal, "Argument given with %s was not a valid number", argument);
      return false;
    }
    else
    {
      *dest = floatVal;
      if (wasReallySet) *wasReallySet = true;
      return true;
    }
  }
  else
  {
    ArLog::log(ArLog::Normal, "No argument given with %s", argument);
    return false;
  }
}
