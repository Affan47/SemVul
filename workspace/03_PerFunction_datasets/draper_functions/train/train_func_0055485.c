check_xline(struct Client *source_p)
{
  struct ConfItem *conf = NULL;
  const char *reason = NULL;

  if ((conf = find_matching_name_conf(XLINE_TYPE, source_p->info, NULL, NULL, 0)) ||
      (conf = find_matching_name_conf(RXLINE_TYPE, source_p->info, NULL, NULL, 0)))
  {
    struct MatchItem *reg = map_to_conf(conf);

    ++reg->count;

    if (reg->reason != NULL)
      reason = reg->reason;
    else
      reason = "No Reason";

    sendto_realops_flags(UMODE_REJ, L_ALL,
                         "X-line Rejecting [%s] [%s], user %s [%s]",
                         source_p->info, reason,
                         get_client_name(source_p, HIDE_IP),
                         source_p->sockhost);

    ++ServerStats.is_ref;
    if (REJECT_HOLD_TIME > 0)
    {
      sendto_one(source_p, ":%s NOTICE %s :Bad user info",
                 me.name, source_p->name);
      source_p->localClient->reject_delay = CurrentTime + REJECT_HOLD_TIME;
      SetCaptured(source_p);
    }
    else
      exit_client(source_p, &me, "Bad user info");
    return 1;
  }

  return 0;
}
