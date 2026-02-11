_ircclient_got_details(struct ircproxy *p, const char *newusername,
                                  const char *newmode, const char *unused,
                                  const char *newrealname) {
  int mode;

  if (!p->username)
    p->username = x_strdup(newusername);

  if (!p->realname)
    p->realname = x_strdup(newrealname);


  mode = atoi(newmode);
  if (mode & RFC2812_MODE_W)
    ircclient_change_mode(p, "+w");
  if (mode & RFC2812_MODE_I)
    ircclient_change_mode(p, "+w");


  p->client_status |= IRC_CLIENT_GOTUSER;

  return 0;
}
