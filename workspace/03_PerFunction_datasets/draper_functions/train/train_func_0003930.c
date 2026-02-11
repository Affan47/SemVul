fillGlobals (hist)
     char *hist;
{
  char name[NAME_MAX+1], type[TYPE_MAX];

  strcpy (name, af_afname (hist));
  strcpy (type, af_aftype (hist));

  if (af_getkey (examineDir, name, type, AF_FIRSTVERS, AF_FIRSTVERS, &firstAso) != -1)
    firstExists = TRUE;

  if (af_getkey (examineDir, name, type, AF_LASTVERS, AF_LASTVERS, &lastAso) != -1)
    lastExists = TRUE;

  if (af_getkey (examineDir, name, type, AF_BUSYVERS, AF_BUSYVERS, &busyAso) != -1)
    busyExists = TRUE;

  if (af_access (examineDir, name, type, AF_CLASS_DERIVED) != -1)
    cachedExist = TRUE;
}
