atFileClassExt (aso)
     Af_key *aso;
{
  static char classStr[4];
  char    *strPtr = classStr;
  mode_t  mode;
  Af_user *locker;

  classStr[0] = classStr[1] = classStr[2] = classStr[3] = '\0';

  mode = af_retnumattr (aso, AF_ATTMODE);

  if (S_ISDIR (mode))
    *strPtr++ = '/';
#ifdef S_ISLNK
  else if (S_ISLNK (mode))
    *strPtr++ = '@';
#endif
#ifdef S_ISSOCK
  else if (S_ISSOCK (mode))
    *strPtr++ = '=';
#endif
  else if ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH))
    *strPtr++ = '*';

  if (af_retnumattr (aso, AF_ATTSTATE) == AF_DERIVED)
    *strPtr++ = '$';
  else {
    locker = af_testlock (aso);
    if (locker->af_username[0])
      *strPtr++ = '^';
  }
  return (classStr);
}
