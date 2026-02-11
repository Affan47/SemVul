_cupsSetLocale(char *argv[])
{
  int		i;
  char		buffer[8192];
  _cups_globals_t *cg;
#ifdef LC_TIME
  const char	*lc_time;
  char		new_lc_time[255],
		*charset;
#endif


  setlocale(LC_ALL, "");

#ifdef LC_TIME
  if ((lc_time = setlocale(LC_TIME, NULL)) == NULL)
    lc_time = setlocale(LC_ALL, NULL);

  if (lc_time)
  {
    strlcpy(new_lc_time, lc_time, sizeof(new_lc_time));
    if ((charset = strchr(new_lc_time, '.')) == NULL)
      charset = new_lc_time + strlen(new_lc_time);

    strlcpy(charset, ".UTF-8", sizeof(new_lc_time) - (charset - new_lc_time));
  }
  else
    strlcpy(new_lc_time, "C", sizeof(new_lc_time));

  setlocale(LC_TIME, new_lc_time);
#endif


  cg = _cupsGlobals();

  if (!cg->lang_default)
    cg->lang_default = cupsLangDefault();


  if (cg->lang_default->encoding != CUPS_US_ASCII &&
      cg->lang_default->encoding != CUPS_UTF8)
  {
    for (i = 1; argv[i]; i ++)
    {


      if (cupsCharsetToUTF8((cups_utf8_t *)buffer, argv[i], sizeof(buffer),
                            cg->lang_default->encoding) < 0)
        continue;


      if (strcmp(buffer, argv[i]))
        argv[i] = strdup(buffer);
    }
  }
}
