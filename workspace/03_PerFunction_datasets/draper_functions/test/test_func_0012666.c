getArgInt(size_t whichArg) const
{
  const char *str;
  int ret;
  char *endPtr;
  if (whichArg > myArgc || getArg(whichArg) == NULL)
    return 0;

  str = getArg(whichArg);
  ret = strtol(str, &endPtr, 10);
  if (endPtr[0] == '\0' && endPtr != str)
    return ret;
  else
    return 0;
}
