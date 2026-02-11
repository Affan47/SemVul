of_reverse(const struct optioninfo *oi, const char *arg, const char *arg2) {
  struct query_node *qun;
  int quflags, r;
  struct sockaddr_in sa;

  memset(&sa,0,sizeof(sa));
  sa.sin_family= AF_INET;
  if (!inet_aton(arg,&sa.sin_addr)) usageerr("invalid IP address %s",arg);

  prep_query(&qun,&quflags);
  qun->owner= xmalloc(strlen(arg) + strlen(arg2) + 2);
  sprintf(qun->owner, "%s %s", arg,arg2);
  r= adns_submit_reverse_any(ads,
			     (struct sockaddr*)&sa, arg2,
			     ov_type == adns_r_none ? adns_r_txt : ov_type,
			     quflags,
			     qun,
			     &qun->qu);
  if (r) sysfail("adns_submit_reverse",r);

  LIST_LINK_TAIL(outstanding,qun);
}
