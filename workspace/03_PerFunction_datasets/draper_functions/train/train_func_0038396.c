getArgBool(size_t whichArg,
                                            bool *ok) const
{
  bool isSuccess = false;
  bool ret = false;

  const char *str = getArg(whichArg);


  if (str != NULL) {

    if (strcasecmp(str, "true") == 0 ||
        strcasecmp(str, "1") == 0) {
      isSuccess = true;
      ret = true;
    }
    else if (strcasecmp(str, "false") == 0 ||
             strcasecmp(str, "0") == 0) {
      isSuccess = true;
      ret = false;
    }
  }

  if (ok != NULL) {
    *ok = isSuccess;
  }
  if (isSuccess) {
    return ret;
  }
  else {
    return 0;
  }
}
