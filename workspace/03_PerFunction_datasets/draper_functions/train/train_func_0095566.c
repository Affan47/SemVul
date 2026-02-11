drawbot(void)
{
  char tchar = 0;
  int len;
  int maxlen;

  if ((gdata.background == 2) || gdata.noscreen)
    {
      return;
    }

  len = strlen(gdata.console_input_line);

  maxlen = gdata.termcols - (gdata.user_nick ? 17+strlen(gdata.user_nick) : 17);

  if (maxlen < 0)
    {
      maxlen = 0;
    }

  if ((len > maxlen))
    {
      tchar = gdata.console_input_line[maxlen];
      gdata.console_input_line[maxlen] = '\0';
    }


  tostdout("\x1b[%d;1H[ iroffer (%s) > %-*s]",
           gdata.termlines,
           (gdata.user_nick ? gdata.user_nick : ""),
           gdata.termcols - (int)(gdata.user_nick ? 16+strlen(gdata.user_nick) : 16),
           gdata.console_input_line);


  tostdout("\x1b[%d;%dH",
           gdata.termlines,
           ((gdata.curcol > maxlen) ? maxlen : gdata.curcol) + (gdata.user_nick ? 16+(int)strlen(gdata.user_nick) : 16));

  if ((len > maxlen))
    {
      gdata.console_input_line[maxlen] = tchar;
    }

  return;
}
