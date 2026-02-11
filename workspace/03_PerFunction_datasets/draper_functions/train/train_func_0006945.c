readconfigenvtext(adns_state ads, const char *envvar) {
  const char *textdata;

  if (ads->iflags & adns_if_noenv) {
    adns__debug(ads,-1,0,"not checking environment variable `%s'",envvar);
    return;
  }
  textdata= instrum_getenv(ads,envvar);
  if (textdata) readconfigtext(ads,textdata,envvar);
}
