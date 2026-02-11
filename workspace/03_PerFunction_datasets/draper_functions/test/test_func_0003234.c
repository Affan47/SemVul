server_report(int idx, int details)
{
  char s1[64], s[128];
  int servidx;

  if (server_online) {
    dprintf(idx, "    Online as: %s%s%s (%s)\n", botname, botuserhost[0] ?
            "!" : "", botuserhost[0] ? botuserhost : "", botrealname);
    if (nick_juped)
      dprintf(idx, "    NICK IS JUPED: %s%s\n", origbotname,
              keepnick ? " (trying)" : "");
    daysdur(now, server_online, s1);
    egg_snprintf(s, sizeof s, "(connected %s)", s1);
    if (server_lag && !waiting_for_awake) {
      if (server_lag == -1)
        egg_snprintf(s1, sizeof s1, " (bad pong replies)");
      else
        egg_snprintf(s1, sizeof s1, " (lag: %ds)", server_lag);
      strcat(s, s1);
    }
  }

  if ((trying_server || server_online) &&
      ((servidx = findanyidx(serv)) != -1)) {
    dprintf(idx, "    Server %s:%d %s\n", dcc[servidx].host, dcc[servidx].port,
            trying_server ? "(trying)" : s);
  } else
    dprintf(idx, "    %s\n", IRC_NOSERVER);

  if (modeq.tot)
    dprintf(idx, "    %s %d%% (%d msgs)\n", IRC_MODEQUEUE,
            (int) ((float) (modeq.tot * 100.0) / (float) maxqmsg),
            (int) modeq.tot);
  if (mq.tot)
    dprintf(idx, "    %s %d%% (%d msgs)\n", IRC_SERVERQUEUE,
            (int) ((float) (mq.tot * 100.0) / (float) maxqmsg), (int) mq.tot);
  if (hq.tot)
    dprintf(idx, "    %s %d%% (%d msgs)\n", IRC_HELPQUEUE,
            (int) ((float) (hq.tot * 100.0) / (float) maxqmsg), (int) hq.tot);

  if (details) {
    int size = server_expmem();

    if (min_servs)
      dprintf(idx, "    Requiring a network with at least %d server%s\n",
              min_servs, (min_servs != 1) ? "s" : "");
    if (initserver[0])
      dprintf(idx, "    On connect, I do: %s\n", initserver);
    if (connectserver[0])
      dprintf(idx, "    Before connect, I do: %s\n", connectserver);
    dprintf(idx, "    Msg flood: %d msg%s/%d second%s\n", flud_thr,
            (flud_thr != 1) ? "s" : "", flud_time,
            (flud_time != 1) ? "s" : "");
    dprintf(idx, "    CTCP flood: %d msg%s/%d second%s\n", flud_ctcp_thr,
            (flud_ctcp_thr != 1) ? "s" : "", flud_ctcp_time,
            (flud_ctcp_time != 1) ? "s" : "");
    dprintf(idx, "    Using %d byte%s of memory\n", size,
            (size != 1) ? "s" : "");
  }
}
