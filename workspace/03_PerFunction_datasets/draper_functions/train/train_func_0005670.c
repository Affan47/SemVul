copyValue(const char *str, Uint32 idx, OFString& target)
{
  target.clear();
  if (str)
  {
    char c = '\\';
    while (idx)
    {
      c = *str++;
      if (c == 0) idx=0; else if (c == '\\') idx--;
    }
    if (c=='\\')
    {
      const char *endstr = str;
      while ((*endstr) && (*endstr != '\\')) endstr++;
      target.assign(str,(endstr-str));
    }
  }
  return;
}
