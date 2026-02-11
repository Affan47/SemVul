handleVersions (option, arg)
     char *option, *arg;
{
  char *genPtr, *revPtr;

  if (!arg || !(*arg)) {
    sprintf (stMessage, "No version number specified -- '%s' ignored.", option);
    stLog (stMessage, ST_LOG_ERROR);
    return (1);
  }
  bindExact.baselineType = AT_BIND_VNUM;

  if (!strcmp (arg, "busy")) {
    bindExact.baselineGen = AF_BUSYVERS;
    bindExact.baselineRev = AF_BUSYVERS;
    return 0;
  }
  genPtr = arg;
  if ((revPtr = strchr (arg, '.'))) {
    *revPtr = '\0';
    revPtr++;
  }
  bindExact.baselineGen =  bindExact.baselineRev = AF_NOVNUM;
  if (genPtr && *genPtr)
    bindExact.baselineGen = atoi (genPtr);
  if (revPtr && *revPtr)
    bindExact.baselineRev = atoi (revPtr);
  return 0;
}
