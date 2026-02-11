isInstance(const char *uid)
{
  if (uid && (sopInstanceUID == uid)) return OFTrue;
  return OFFalse;
}
