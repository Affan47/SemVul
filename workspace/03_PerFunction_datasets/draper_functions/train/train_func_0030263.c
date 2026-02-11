GetInteger (char *data, int *val){
  char *endPtr;
  long int retVal;

  assert (val);

  errno = 0;
  retVal = strtol (data, &endPtr, 0);
  if (retVal == 0 && (errno != 0 || data == endPtr)) return false;
  if (errno != 0 && (retVal == LONG_MAX || retVal == LONG_MIN)) return false;
  if (retVal < (long) INT_MIN || retVal > (long) INT_MAX) return false;
  *val = (int) retVal;
  return true;
}
