share_ufsend(int idx, char *par)
{
  char *ip = NULL, *port;
  char s[1024];
  int i, sock;
  FILE *f;

  egg_snprintf(s, sizeof s, ".share.%s.%li.users", botnetnick, now);
  if (!(b_status(idx) & STAT_SHARE)) {
    dprintf(idx, "s e You didn't ask; you just started sending.\n");
    dprintf(idx, "s e Ask before sending the userfile.\n");
    zapfbot(idx);
  } else if (dcc_total == max_dcc) {
    putlog(LOG_MISC, "*", "NO MORE DCC CONNECTIONS -- can't grab userfile");
    dprintf(idx, "s e I can't open a DCC to you; I'm full.\n");
    zapfbot(idx);
  } else if (!(f = fopen(s, "wb"))) {
    putlog(LOG_MISC, "*", "CAN'T WRITE USERFILE DOWNLOAD FILE!");
    zapfbot(idx);
  } else {
    ip = newsplit(&par);
    port = newsplit(&par);
    sock = getsock(SOCK_BINARY);
    if (sock < 0 || open_telnet_dcc(sock, ip, port) < 0) {
      killsock(sock);
      putlog(LOG_BOTS, "*", "Asynchronous connection failed!");
      dprintf(idx, "s e Can't connect to you!\n");
      zapfbot(idx);
    } else {
      i = new_dcc(&DCC_FORK_SEND, sizeof(struct xfer_info));
      dcc[i].addr = my_atoul(ip);
      dcc[i].port = atoi(port);
      strcpy(dcc[i].nick, "*users");
      dcc[i].u.xfer->filename = nmalloc(strlen(s) + 1);
      strcpy(dcc[i].u.xfer->filename, s);
      dcc[i].u.xfer->origname = dcc[i].u.xfer->filename;
      dcc[i].u.xfer->length = atoi(par);
      dcc[i].u.xfer->f = f;
      dcc[i].sock = sock;
      strcpy(dcc[i].host, dcc[idx].nick);

      dcc[idx].status |= STAT_GETTING;
    }
  }
}
