hts_addurl(httrackp * opt, char **url) {
  if (url)
    opt->state._hts_addurl = url;
  return (opt->state._hts_addurl != NULL);
}
