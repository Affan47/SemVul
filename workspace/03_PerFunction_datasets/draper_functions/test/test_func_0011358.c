set_lang (var, value)
     char *var, *value;
{
  FREE (lang);
  if (value)
    lang = savestring (value);
  else
    {
      lang = (char *)xmalloc (1);
      lang[0] = '\0';
    }

  return ((lc_all == 0 || *lc_all == 0) ? reset_locale_vars () : 0);
}
