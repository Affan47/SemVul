prep_query(struct query_node **qun_r, int *quflags_r) {
  struct query_node *qun;
  char idbuf[20];

  if (ov_pipe && !ads) usageerr("-f/--pipe not consistent with domains on command line");
  ensure_adns_init();

  qun= malloc(sizeof(*qun));
  qun->pqfr= ov_pqfr;
  if (ov_id) {
    qun->id= xstrsave(ov_id);
  } else {
    sprintf(idbuf,"%lu",idcounter++);
    idcounter &= 0x0fffffffflu;
    qun->id= xstrsave(idbuf);
  }

  *quflags_r=
    (ov_search ? adns_qf_search : 0) |
    (ov_tcp ? adns_qf_usevc : 0) |
    ((ov_pqfr.show_owner || ov_format == fmt_simple) ? adns_qf_owner : 0) |
    (ov_qc_query ? adns_qf_quoteok_query : 0) |
    (ov_qc_anshost ? adns_qf_quoteok_anshost : 0) |
    (ov_qc_cname ? 0 : adns_qf_quoteok_cname) |
    ov_cname,

  *qun_r= qun;
}
