_ircclient_handle_jump(struct ircproxy *p, struct ircmessage msg) {
  struct strlist *server;


  if (msg.numparams >= 2) {
    struct strlist *s;
    int i;


    server = 0;
    s = p->conn_class->servers;
    i = 0;
    while (s) {
      if ((atoi(msg.params[1]) == ++i)
          || !irc_strcasecmp(msg.params[1], s->str)) {
        server = s;
        break;
      }

      s = s->next;
    }

  } else {

    server = 0;
    if (p->conn_class->next_server)
      server = p->conn_class->next_server->next;
    if (!server)
      server = p->conn_class->servers;
  }


  if (!server && p->conn_class->allow_jump_new
      && (msg.numparams >= 2)) {
    debug("New server");

    server = (struct strlist *)malloc(sizeof(struct strlist));
    server->str = x_strdup(msg.params[1]);
    server->next = 0;

    if (p->conn_class->servers) {
      struct strlist *ss;

      ss = p->conn_class->servers;
      while (ss->next)
        ss = ss->next;

      ss->next = server;
    } else {
      p->conn_class->servers = server;
    }

  } else if (!server) {
    ircclient_send_numeric(p, 402, "No such server, "
                           "use /DIRCPROXY SERVERS to see them");
  }

  if (server) {
    debug("Jumping to %s", server->str);

    p->conn_class->next_server = server;
    ircserver_connectagain(p);


    ircprot_freemsg(&msg);
    return 1;
  } else {
    return 0;
  }
}
