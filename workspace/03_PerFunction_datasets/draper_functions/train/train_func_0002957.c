get_token(bool skipseparator, bool compat)
{
  GUTF8String str;
  int c = get_spaces(skipseparator);
  if (c == EOF)
    {
      return str;
    }
  if (!skipseparator && (c=='\n' || c=='\r' || c==';'))
    {
      unget(c);
      return str;
    }
  if (c != '\"' && c != '\'')
    {
      while (c!=' ' && c!='\t' && c!='\r' && c!=';'
             && c!='\n' && c!='#' && c!=EOF)
        {
          str += c;
          c = get();
        }
      unget(c);
    }
  else
    {
      int delim = c;
      c = get();
      while (c != delim && c!=EOF)
        {
          if (c == '\\')
            {
              c = get();
              if (compat && c!='\"')
                {
                  str += '\\';
                }
              else if (c>='0' && c<='7')
                {
                  int x = 0;
                  {
                    for (int i=0; i<3 && c>='0' && c<='7'; i++)
                    {
                      x = x * 8 + c - '0';
                      c = get();
                    }
                  }
                  unget(c);
                  c = x;
                }
              else
                {
                  const char *tr1 = "tnrbfva";
                  const char *tr2 = "\t\n\r\b\f\013\007";
                  {
                    for (int i=0; tr1[i]; i++)
                    {
                      if (c == tr1[i])
                        c = tr2[i];
                    }
                  }
                }
            }
          if (c != EOF)
            str += c;
          c = get();
        }
    }
  return str;
}
