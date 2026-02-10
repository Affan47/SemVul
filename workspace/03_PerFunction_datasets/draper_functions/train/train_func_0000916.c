info (ACE_TCHAR **strp,
                          size_t length) const
{
  ACE_TRACE ("ACE_Naming_Context::info");

  ACE_TCHAR buf[BUFSIZ];

  ACE_OS::sprintf (buf,
                   ACE_TEXT ("%s\t#%s\n"),
                   ACE_TEXT ("ACE_Naming_Context"),
                   ACE_TEXT ("Proxy for making calls to a Name Server"));

  if (*strp == 0 && (*strp = ACE_OS::strdup (buf)) == 0)
    return -1;
  else
    ACE_OS::strsncpy (*strp, buf, length);
  return static_cast<int> (ACE_OS::strlen (buf));
}
