botaddr_gotshare(struct userrec *u, struct user_entry *e,
                            char *buf, int idx)
{
  struct bot_addr *bi = user_malloc(sizeof(struct bot_addr));
  char *arg;

  egg_bzero(bi, sizeof(struct bot_addr));
  arg = newsplit(&buf);
  bi->address = user_malloc(strlen(arg) + 1);
  strcpy(bi->address, arg);
  arg = newsplit(&buf);
  bi->telnet_port = atoi(arg);
  bi->relay_port = atoi(buf);
  if (!bi->telnet_port)
    bi->telnet_port = 3333;
  if (!bi->relay_port)
    bi->relay_port = bi->telnet_port;
  if (!(dcc[idx].status & STAT_GETTING))
    putlog(LOG_CMDS, "*", "%s: change botaddr %s", dcc[idx].nick, u->handle);
  return botaddr_set(u, e, bi);
}
