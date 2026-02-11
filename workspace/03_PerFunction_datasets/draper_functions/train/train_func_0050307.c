stats_servers_verbose(struct Client* sptr, const struct StatDesc* sd,
		      char* param)
{
  struct Client *acptr;
  const char *fmt;


  if (sd->sd_funcdata) {
    send_reply(sptr, SND_EXPLICIT | RPL_STATSVERBOSE,
               "%-20s %-20s Flags Hops Numeric   Lag  RTT   Up Down "
               "Clients/Max Proto %-10s :Info", "Servername", "Uplink",
               "LinkTS");
    fmt = "%-20s %-20s %c%c%c%c%c  %4i %s %-4i %5i %4i %4i %4i %5i %5i P%-2i   %Tu :%s";
  } else {
    fmt = "%s %s %c%c%c%c%c %i %s %i %i %i %i %i %i %i P%i %Tu :%s";
  }

  for (acptr = GlobalClientList; acptr; acptr = cli_next(acptr))
  {
    if (!IsServer(acptr) && !IsMe(acptr))
      continue;

    if (param && match(param, cli_name(acptr)))
      continue;
    send_reply(sptr, SND_EXPLICIT | RPL_STATSVERBOSE, fmt,
               cli_name(acptr),
               cli_name(cli_serv(acptr)->up),
               IsBurst(acptr) ? 'B' : '-',
               IsBurstAck(acptr) ? 'A' : '-',
               IsHub(acptr) ? 'H' : '-',
               IsService(acptr) ? 'S' : '-',
               IsIPv6(acptr) ? '6' : '-',
               cli_hopcount(acptr),
               NumServ(acptr),
               base64toint(cli_yxx(acptr)),
               cli_serv(acptr)->lag,
               cli_serv(acptr)->asll_rtt,
               cli_serv(acptr)->asll_to,
               cli_serv(acptr)->asll_from,
               (acptr == &me ? UserStats.local_clients : cli_serv(acptr)->clients),
               cli_serv(acptr)->nn_mask,
               cli_serv(acptr)->prot,
               cli_serv(acptr)->timestamp,
               cli_info(acptr));
  }
}
