setPrivateKeyPasswd(const char *thePasswd)
{
  if (thePasswd) privateKeyPasswd = thePasswd;
  else privateKeyPasswd.clear();
  usePrivateKeyPassword = OFTrue;
  return;
}
