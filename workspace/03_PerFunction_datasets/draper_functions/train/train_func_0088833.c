mo_stats(struct Client *client_p, struct Client *source_p,
         int parc, char *parv[])
{
  if (hunt_server(client_p, source_p, ":%s STATS %s :%s", 2,
                  parc, parv) != HUNTED_ISME)
     return;

  if (!MyClient(source_p) && IsCapable(source_p->from, CAP_TS6) && HasID(source_p))
  {
    from = me.id;
    to = source_p->id;
  }
  else
  {
    from = me.name;
    to = source_p->name;
  }

  do_stats(source_p, parc, parv);
}
