write_xline(struct Client *source_p, char *gecos, char *reason,
	    time_t tkline_time)
{
  struct ConfItem *conf;
  struct MatchItem *match_item;
  const char *current_date;
  time_t cur_time;

  conf = make_conf_item(XLINE_TYPE);
  match_item = map_to_conf(conf);

  collapse(gecos);
  DupString(conf->name, gecos);
  DupString(match_item->reason, reason);
  DupString(match_item->oper_reason, "");
  cur_time = CurrentTime;
  current_date = smalldate(cur_time);

  if (tkline_time != 0)
  {
    sendto_realops_flags(UMODE_ALL, L_ALL,
			 "%s added temporary %d min. X-Line for [%s] [%s]",
			 get_oper_name(source_p), (int)tkline_time/60,
			 conf->name, match_item->reason);
    sendto_one(source_p, ":%s NOTICE %s :Added temporary %d min. X-Line [%s]",
	       MyConnect(source_p) ? me.name : ID_or_name(&me, source_p->from),
	       source_p->name, (int)tkline_time/60, conf->name);
    ilog(L_TRACE, "%s added temporary %d min. X-Line for [%s] [%s]",
	 source_p->name, (int)tkline_time/60,
	 conf->name, match_item->reason);
    match_item->hold = CurrentTime + tkline_time;
    add_temp_line(conf);
  }
  else
    write_conf_line(source_p, conf, current_date, cur_time);
  rehashed_klines = 1;
}
