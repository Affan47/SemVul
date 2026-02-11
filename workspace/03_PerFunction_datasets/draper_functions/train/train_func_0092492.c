restored_object_id (unixname) char *unixname; {


  static char roid[MYMAXNAMLEN];
  struct restoreItem *currentItem;

  if (!(unixname && *unixname))
    return (char *)NULL;

  if (depth >= maxResListDepth)
    return unixname;

  currentItem = restoreList[depth];
  while(currentItem != (struct restoreItem *)0) {
    if (strcmp (unixname, currentItem->unixName) == 0) {
      Af_key *rkey = &currentItem->restoreKey;
      Bool is_busy = af_retnumattr (rkey, AF_ATTSTATE) == AF_BUSY;

      switch (currentItem->restoreType) {
      case REGULAR:
	strcpy (roid, af_retattr (rkey, is_busy ? AF_ATTUNIXNAME : AF_ATTBOUND));
	break;
      case VPATH:
	strcpy (roid, af_retattr (rkey, AF_ATTSPATH) + strlen (curvpath[0]) + 1);
	strcat (roid, "/");
	strcat (roid, af_retattr (rkey, is_busy ? AF_ATTUNIXNAME : AF_ATTBOUND));
	break;
      case EXTERNAL:
	strcpy (roid, af_retattr (rkey, AF_ATTSPATH));
	strcat (roid, "/");
	strcat (roid, af_retattr (rkey, is_busy ? AF_ATTUNIXNAME : AF_ATTBOUND));
	break;
      default:
	fprintf (stderr, "internal error: wrong switch in `restored_object_id'.\n");
	return (char *)NULL;
      }
      return roid;
    }
    currentItem = currentItem->next;
  }
  return unixname;
}
