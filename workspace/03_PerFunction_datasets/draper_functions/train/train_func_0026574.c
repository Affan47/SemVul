urltosavepath(const char *savedir, const char *url){
  CBDATUM *buf;
  CBLIST *elems;
  const char *rp;
  int i;
  if((rp = strstr(url, "://")) != NULL) url = rp + 3;
  buf = cbdatumopen(NULL, -1);
  elems = cbsplit(url, -1, "/");
  if(cbstrbwmatch(url, "/")) cblistpush(elems, "index.html", -1);
  cbdatumprintf(buf, "%s", savedir);
  for(i = 0; i < cblistnum(elems); i++){
    rp = cblistval(elems, i, NULL);
    if(rp[0] == '\0') continue;
    est_mkdir(cbdatumptr(buf));
    unlink(cbdatumptr(buf));
    cbdatumprintf(buf, "%c%?", ESTPATHCHR, rp);
  }
  cblistclose(elems);
  return cbdatumtomalloc(buf, NULL);
}
