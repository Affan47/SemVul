write_rxline(struct Client *source_p, const char *gecos, char *reason,
             time_t tkline_time)
{
  struct ConfItem *conf = NULL;
  struct MatchItem *match_item = NULL;
  const char *current_date = NULL;
  time_t cur_time = 0;
  void *exp_gecos = NULL;
  const char *errptr = NULL;

  if (!(exp_gecos = ircd_pcre_compile(gecos, &errptr)))
  {
    sendto_realops_flags(UMODE_ALL, L_ALL,
           "Failed to add regular expression based X-Line: %s", errptr);
    return;
  }

  conf = make_conf_item(RXLINE_TYPE);
  conf->regexpname = exp_gecos;

  match_item = map_to_conf(conf);

  DupString(conf->name, gecos);
  DupString(match_item->reason, reason);
  DupString(match_item->oper_reason, "");

  cur_time = CurrentTime;
  current_date = smalldate(cur_time);

  if (tkline_time)
  {
    sendto_realops_flags(UMODE_ALL, L_ALL,
                         "%s added temporary %d min. RX-Line for [%s] [%s]",
                         get_oper_name(source_p), (int)tkline_time/60,
                         conf->name, match_item->reason);
    sendto_one(source_p, ":%s NOTICE %s :Added temporary %d min. RX-Line [%s]",
               MyConnect(source_p) ? me.name : ID_or_name(&me, source_p->from),
               source_p->name, (int)tkline_time/60, conf->name);
    ilog(L_TRACE, "%s added temporary %d min. RX-Line for [%s] [%s]",
         source_p->name, (int)tkline_time/60,
         conf->name, match_item->reason);
    match_item->hold = CurrentTime + tkline_time;
    add_temp_line(conf);
  }
  else
    write_conf_line(source_p, conf, current_date, cur_time);
  rehashed_klines = 1;
}
