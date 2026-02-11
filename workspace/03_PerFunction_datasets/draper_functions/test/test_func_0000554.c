ruleExpandCommand (str)
     char *str;
{
  char   *newString, *newPtr, *endPtr, *ptr = str;
  char   resultBuf[10240];
  size_t newSize = 0, maxSize = 256;
  int    resultLen;
  FILE   *fileDes;

  if ((newString = malloc (maxSize)) == NULL) {
    atBindError = TRUE;
    strcpy (atBindErrorMsg, "not enough memory");
    return (NULL);
  }

  newPtr = newString;

  while ((*newPtr = *ptr)) {
    needSpace (1);
    if (*ptr != '`') {
      newPtr++;
      ptr++;
      continue;
    }

    ptr++;
    if ((endPtr = strchr (ptr, '`')) == NULL) {
      newPtr++;
      continue;
    }
    *endPtr = '\0';

    if ((fileDes = popen (ptr, "r")) == NULL) {
      atBindError = TRUE;
      strcpy (atBindErrorMsg, "error during popen");
      return (NULL);
    }

    if (fgets (resultBuf, 10240, fileDes) == NULL) {
      resultBuf[0] = '\0';
    }
    resultBuf[10240-1] = '\0';
    pclose(fileDes);

    resultLen = strlen (resultBuf);
    needSpace (resultLen);
    strncpy (newPtr, resultBuf, resultLen);
    newPtr += resultLen;

    *endPtr = '`';
    ptr = endPtr+1;
  }

  return (newString);
}
