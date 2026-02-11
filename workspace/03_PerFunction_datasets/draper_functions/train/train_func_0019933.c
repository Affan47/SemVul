readline(FILE *inf, adns_state adns, int opts) {
  static char buf[MAXLINE];
  char *str;
  logline *line;

  if (fgets(buf, MAXLINE, inf)) {
    str= malloc(sizeof(*line) + strlen(buf) + 1);
    if (!str) aargh("malloc");
    line= (logline*)str;
    line->next= NULL;
    line->start= str+sizeof(logline);
    strcpy(line->start, buf);
    str= ipaddr2domain(line->start, &line->addr, &line->rest);
    if (opts & OPT_DEBUG)
      msg("submitting %.*s -> %s", (int)(line->rest-line->addr), guard_null(line->addr), str);
    if (adns_submit(adns, str, adns_r_ptr,
		    adns_qf_quoteok_cname|adns_qf_cname_loose,
		    NULL, &line->query))
      aargh("adns_submit");
    return line;
  }
  if (!feof(inf))
    aargh("fgets");
  return NULL;
}
