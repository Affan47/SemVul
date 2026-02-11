basename(const GUTF8String &gfname, const char *suffix)
{
  if(!gfname.length())
    return gfname;

  const char *fname=gfname;
#if defined(WIN32) || defined(OS2)

  if (fname[1] == colon)
  {
    if(!fname[2])
    {
      return gfname;
    }
    if (!fname[3] && (fname[2]== slash || fname[2]== backslash))
    {
      char string_buffer[4];
      string_buffer[0] = fname[0];
      string_buffer[1] = colon;
      string_buffer[2] = backslash;
      string_buffer[3] = 0;
      return string_buffer;
    }
  }
#endif


  GUTF8String retval(gfname,finddirsep(gfname)+1,(unsigned int)(-1));
  fname=retval;


  if (suffix)
  {
    if (suffix[0]== dot )
      suffix ++;
    if (suffix[0])
    {
      const GUTF8String gsuffix(suffix);
      const int sl = gsuffix.length();
      const char *s = fname + strlen(fname);
      if (s > fname + sl)
      {
        s = s - (sl + 1);
        if(*s == dot && (GUTF8String(s+1).downcase() == gsuffix.downcase()))
        {
          retval.setat((int)((size_t)s-(size_t)fname),0);
        }
      }
    }
  }
  return retval;
}
