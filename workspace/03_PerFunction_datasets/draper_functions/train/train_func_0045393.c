stats_ltrace(struct Client *source_p, int parc, char *parv[])
{
  int doall = 0;
  int wilds = 0;
  char *name = NULL;
  char statchar;

  if ((name = parse_stats_args(parc, parv, &doall, &wilds)) != NULL)
  {
    statchar = parv[1][0];

    stats_L(source_p, name, doall, wilds, statchar);
  }
  else
    sendto_one(source_p, form_str(ERR_NEEDMOREPARAMS),
               from, to, "STATS");
}
