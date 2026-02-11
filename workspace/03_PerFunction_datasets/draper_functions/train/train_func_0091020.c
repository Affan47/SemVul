get_langfile(lang_sec *sec)
{
  char *langfile;
  lang_pri *lp;

  for (lp = langpriority; lp; lp = lp->next) {

    if (sec->lang && !strcmp(sec->lang, lp->lang))
      return NULL;
    langfile = get_specific_langfile(lp->lang, sec);
    if (langfile)
      return langfile;
  }

  if (sec->lang)
    nfree(sec->lang);
  sec->lang = NULL;
  return NULL;
}
