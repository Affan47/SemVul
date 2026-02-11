u_servers(const userinput * const u)
{
  int i;
  server_t *ss;

  updatecontext();

  u_respond(u,"Server List:");
  u_respond(u,"  Num  Server                         Port  Password");

  ss = irlist_get_head(&gdata.servers);
  i = 1;
  while(ss)
    {
      u_respond(u,"  %3i  %-27s  %6u  %s",
                i,
                ss->hostname,
                ss->port,
                ss->password ? "(hidden)" : "(none)");
      ss = irlist_get_next(ss);
      i++;
    }

  u_respond(u,"Current Server: %s:%u (%s)",
            gdata.curserver.hostname,
            gdata.curserver.port,
            gdata.curserveractualname ? gdata.curserveractualname : "<unknown>");

}
