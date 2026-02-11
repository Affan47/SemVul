attach (SANE_String_Const devname)
{
  scanner_info_t *si;

  si = (scanner_info_t *) calloc (1, sizeof (*si));
  if (!si)
    return SANE_STATUS_NO_MEM;
  si->devname = strdup (devname);
  if (!si->devname)
    return SANE_STATUS_NO_MEM;
  si -> interface = INT_USB;
  si->next = first_scanner;
  first_scanner = si;
  nscanners++;
  return SANE_STATUS_GOOD;
}
