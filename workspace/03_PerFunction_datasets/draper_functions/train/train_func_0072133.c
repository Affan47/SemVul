setContext(const char *language,
			    const char *package,
			    const char *searchpath)
{
  tstring t;
  string *s;
  FILE *f;
  char fname[64], fname2[64], dicfile[512];

  if (language == 0)
    guessLanguage();
  else
    setLanguage(language);

  if (strlen(package) > 31)
    return;
  strcpy(Package, package);

  snprintf(fname2,64,"%s.%s.dict",Package,Lang);
  if (SubLang[0] != 0)
    snprintf(fname,64,"%s.%s_%s.dict",Package,Lang,SubLang);
  else
    strcpy(fname, fname2);

  t.set(searchpath);

  while((s=t.token(":"))!=0) {
    snprintf(dicfile,512,"%s/%s",s->c_str(), fname);
    f = fopen(dicfile,"r");
    if (f==0) {
      snprintf(dicfile,512,"%s/%s",s->c_str(), fname2);
      f = fopen(dicfile,"r");
    }
    if (f!=0) {
      ready = loadDictionary(f);
      fclose(f);
      return;
    }
  }
}
