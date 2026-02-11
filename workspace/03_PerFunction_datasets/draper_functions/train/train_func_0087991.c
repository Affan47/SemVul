log_heartbeat(time_t now)
{
  char *bw_sent = NULL;
  char *bw_rcvd = NULL;
  char *uptime = NULL;
  const routerinfo_t *me;

  const or_options_t *options = get_options();
  (void)now;

  if (public_server_mode(options)) {

    if (!(me = router_get_my_routerinfo()))
      return -1;
    else
      if (!node_get_by_id(me->cache_info.identity_digest))
        log_fn(LOG_NOTICE, LD_HEARTBEAT, "Heartbeat: It seems like we are not "
               "in the cached consensus.");
  }

  uptime = secs_to_uptime(get_uptime());
  bw_rcvd = bytes_to_usage(get_bytes_read());
  bw_sent = bytes_to_usage(get_bytes_written());

  log_fn(LOG_NOTICE, LD_HEARTBEAT, "Heartbeat: Tor's uptime is %s, with %d "
         "circuits open. I've sent %s and received %s.",
         uptime, count_circuits(),bw_sent,bw_rcvd);

  tor_free(uptime);
  tor_free(bw_sent);
  tor_free(bw_rcvd);

  return 0;
}
