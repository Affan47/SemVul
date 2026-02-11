cmd_who(struct userrec *u, int idx, char *par)
{
  int i;

  if (par[0]) {
    if (dcc[idx].u.chat->channel < 0) {
      dprintf(idx, "You have chat turned off.\n");
      return;
    }
    putlog(LOG_CMDS, "*", "#%s# who %s", dcc[idx].nick, par);
    if (!egg_strcasecmp(par, botnetnick))
      tell_who(u, idx, dcc[idx].u.chat->channel);
    else {
      i = nextbot(par);
      if (i < 0) {
        dprintf(idx, "That bot isn't connected.\n");
      } else if (dcc[idx].u.chat->channel >= GLOBAL_CHANS)
        dprintf(idx, "You are on a local channel.\n");
      else {
        char s[40];

        simple_sprintf(s, "%d:%s@%s", dcc[idx].sock, dcc[idx].nick, botnetnick);
        botnet_send_who(i, s, par, dcc[idx].u.chat->channel);
      }
    }
  } else {
    putlog(LOG_CMDS, "*", "#%s# who", dcc[idx].nick);
    if (dcc[idx].u.chat->channel < 0)
      tell_who(u, idx, 0);
    else
      tell_who(u, idx, dcc[idx].u.chat->channel);
  }
}
