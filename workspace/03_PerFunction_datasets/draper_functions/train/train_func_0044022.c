readstr_upto(scheme *sc, char *delim) {
  char   *p = sc->strbuff;

  while (!is_one_of(delim, (*p++ = inchar(sc))));
  if(p==sc->strbuff+2 && p[-2]=='\\') {
    *p=0;
  } else {
    backchar(sc,p[-1]);
    *--p = '\0';
  }
  return sc->strbuff;
}
