setArgWithFunctor(ArArgumentBuilder *argument,
					     char *errorBuffer,
					     size_t errorBufferLen,
					     bool doNotSet)
{
  myValueSet = true;
  bool ret = true;
  if (mySetFunctor == NULL)
  {
    ArLog::log(ArLog::Normal, "ArConfigArg of %s: setArgWithFunctor called with NULL pointer.", getName());
    if (errorBuffer != NULL)
      snprintf(errorBuffer, errorBufferLen, "%s pointer is NULL.", getName());
    return false;
  }
  if (!doNotSet)
    ret = mySetFunctor->invokeR(argument);
  return ret;
}
