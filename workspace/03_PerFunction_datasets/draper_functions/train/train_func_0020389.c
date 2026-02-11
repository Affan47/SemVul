af_gid(const struct cmdinfo *cip, const char *value) {
  char *ep;
  unsigned long ul;

  if (opt_ngids >= sizeof(opt_gids)/sizeof(opt_gids[0]))
    badusage("too many gids specified");
  ul= strtoul(value,&ep,0);
  if ((*ep) || (uid_t)ul != ul || ul>INT_MAX) badusage("bad gid `%s'",value);
  opt_gids[opt_ngids++]= ul;
}
