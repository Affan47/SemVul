apply_tkline(struct Client *source_p, struct ConfItem *conf,
             int tkline_time)
{
  struct AccessItem *aconf;

  aconf = (struct AccessItem *)map_to_conf(conf);
  aconf->hold = CurrentTime + tkline_time;
  add_temp_line(conf);
  sendto_realops_flags(UMODE_ALL, L_ALL,
		       "%s added temporary %d min. K-Line for [%s@%s] [%s]",
		       get_oper_name(source_p), tkline_time/60,
		       aconf->user, aconf->host,
		       aconf->reason);
  sendto_one(source_p, ":%s NOTICE %s :Added temporary %d min. K-Line [%s@%s]",
	     MyConnect(source_p) ? me.name : ID_or_name(&me, source_p->from),
	     source_p->name, tkline_time/60, aconf->user, aconf->host);
  ilog(L_TRACE, "%s added temporary %d min. K-Line for [%s@%s] [%s]",
       source_p->name, tkline_time/60,
       aconf->user, aconf->host, aconf->reason);
  log_oper_action(LOG_TEMP_KLINE_TYPE, source_p, "[%s@%s] [%s]\n",
		  aconf->user, aconf->host, aconf->reason);
  rehashed_klines = 1;
}
