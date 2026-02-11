setInt(int val, char *errorBuffer,
				  size_t errorBufferLen, bool doNotSet)
{
  myValueSet = true;
  if (!myIgnoreBounds && val < myMinInt)
  {
    ArLog::log(ArLog::Normal, "ArConfigArg of %s: setInt value %d below range [%d, %d]", getName(), val, myMinInt, myMaxInt);
    if (errorBuffer != NULL)
      snprintf(errorBuffer, errorBufferLen, "%s value of %d is below minimum of %d.", getName(), val, myMinInt);
    return false;
  }
  if (!myIgnoreBounds && val > myMaxInt)
  {
    ArLog::log(ArLog::Normal, "ArConfigArg of %s: setInt value %d above range [%d, %d]", getName(), val, myMinInt, myMaxInt);
    if (errorBuffer != NULL)
      snprintf(errorBuffer, errorBufferLen, "%s value of %d is above maximum of %d.", getName(), val, myMaxInt);
    return false;
  }
  if ((myIntType == INT_INT && myIntPointer == NULL) ||
      (myIntType == INT_SHORT && myIntShortPointer == NULL) ||
      (myIntType == INT_UNSIGNED_SHORT &&
       myIntUnsignedShortPointer == NULL) ||
      (myIntType == INT_UNSIGNED_CHAR && myIntUnsignedCharPointer == NULL))
  {
    ArLog::log(ArLog::Normal, "ArConfigArg of %s: setInt called with NULL int pointer.", getName());
    if (errorBuffer != NULL)
      snprintf(errorBuffer, errorBufferLen, "%s pointer is NULL.", getName());
    return false;
  }

  if (!doNotSet)
  {
    if (myIntType == INT_INT)
      *myIntPointer = val;
    else if (myIntType == INT_SHORT)
      *myIntShortPointer = val;
    else if (myIntType == INT_UNSIGNED_SHORT)
      *myIntUnsignedShortPointer = val;
    else if (myIntType == INT_UNSIGNED_CHAR)
      *myIntUnsignedCharPointer = val;
    else
    {
      ArLog::log(ArLog::Normal, "ArConfigArg of %s: int is bad type.", getName());
      if (errorBuffer != NULL)
	snprintf(errorBuffer, errorBufferLen, "%s int is bad type (%d).", getName(), myIntType);
      return false;
    }
  }
  return true;
}
