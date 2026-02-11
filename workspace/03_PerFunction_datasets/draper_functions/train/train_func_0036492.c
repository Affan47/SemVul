parse_primitive_type_ip_tcp_flags(struct line_parser *lp,
  struct ftfil *ftfil)
{
  struct ftfil_lookup_ip_tcp_flags *ftfliptcp;


  lp->sym_cur = (struct ftsym*)0L;

  ftfliptcp = (struct ftfil_lookup_ip_tcp_flags*)lp->cur_primitive->lookup;

  if (ftfil_load_lookup(lp, lp->word, 256, ftfliptcp->mode, lp->mode)) {
    fterr_warnx("load_lookup(): failed");
    return -1;
  }

  return 0;

}
