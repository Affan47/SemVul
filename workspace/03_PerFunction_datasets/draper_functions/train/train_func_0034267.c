me_kline(struct Client *client_p, struct Client *source_p,
         int parc, char *parv[])
{
  struct ConfItem *conf=NULL;
  struct AccessItem *aconf=NULL;
  int tkline_time;
  const char* current_date;
  time_t cur_time;
  char *kuser, *khost, *kreason, *oper_reason;

  if (parc != 6 || EmptyString(parv[5]))
    return;

  if (!match(parv[1], me.name))
    return;

  tkline_time = valid_tkline(parv[2], TK_SECONDS);
  kuser = parv[3];
  khost = parv[4];
  kreason = parv[5];

  if ((oper_reason = strchr(kreason, '|')) != NULL)
    *oper_reason++ = '\0';

  cur_time = CurrentTime;
  current_date = smalldate(cur_time);

  if (find_matching_name_conf(ULINE_TYPE, source_p->servptr->name,
                              source_p->username, source_p->host,
                              SHARED_KLINE))
  {
    if (!IsClient(source_p) ||
        already_placed_kline(source_p, kuser, khost, YES))
      return;

    conf = make_conf_item(KLINE_TYPE);
    aconf = map_to_conf(conf);
    DupString(aconf->host, khost);
    DupString(aconf->user, kuser);

    if (tkline_time != 0)
    {
      ircsprintf(buffer, "Temporary K-line %d min. - %s (%s)",
                 (int)(tkline_time/60), kreason, current_date);
      DupString(aconf->reason, buffer);

      if (oper_reason != NULL)
        DupString(aconf->oper_reason, oper_reason);
      apply_tkline(source_p, conf, tkline_time);
    }
    else
    {
      ircsprintf(buffer, "%s (%s)", kreason, current_date);
      DupString(aconf->reason, buffer);

      if (oper_reason != NULL)
        DupString(aconf->oper_reason, oper_reason);
      apply_kline(source_p, conf, current_date, cur_time);
    }
  }
}
