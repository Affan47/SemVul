histAddName (hist, longName)
     char *hist;
     int  longName;
{
  static char histVinfo[64];

  if (fastFlag) {
    histVinfo[0] = '\0';
    return (histVinfo);
  }

  if (!internalCall)
    fillGlobals (hist);

  histVinfo[0] = '[';
  histVinfo[1] = '\0';

  if (firstExists) {
    strcat (histVinfo, af_retattr (&firstAso, AF_ATTVERSION));

    if ((lastExists) && (lastAso.af_lpos != firstAso.af_lpos)) {
      strcat (histVinfo, "-");
      strcat (histVinfo, af_retattr (&lastAso, AF_ATTVERSION));
    }

    if (cachedExist & longName)
      strcat (histVinfo, ",cached");
    if (busyExists & longName)
      strcat (histVinfo, ",busy");
    strcat (histVinfo, "]");
  }
  else if (cachedExist) {
    histVinfo[0] = '\0';
    if (busyExists & longName)
      strcpy (histVinfo, "[cached,busy]");
    else
      strcpy (histVinfo, "[]");
  }
  else if (busyExists) {
    histVinfo[0] = '\0';
  }
  else {
    char *namePtr = strrchr (hist, '/');
    if (!namePtr)
      namePtr = hist;
    if (strcmp (namePtr, ".") && strcmp (namePtr, ".."))
      strcpy (histVinfo, "[]");
    else
      histVinfo[0] = '\0';
  }

  if (fileClassFlag) {
    if (busyExists) {
      strcat (histVinfo, atFileClassExt (&busyAso));
    }
    else if (lastExists) {
      strcat (histVinfo, atFileClassExt (&lastAso));
    }
    else if (cachedExist) {
      strcat (histVinfo, "$");
    }
  }

  if (!internalCall)
    destroyGlobals ();
  return (histVinfo);
}
