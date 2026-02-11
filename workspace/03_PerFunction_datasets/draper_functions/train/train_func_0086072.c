do_etrace(struct Client *source_p, int parc, char *parv[])
{
  const char *tname = NULL;
  struct Client *target_p = NULL;
  int wilds = 0;
  int do_all = 0;
  int full_etrace = 0;
  dlink_node *ptr;

  if (parc > 1)
  {
    if (irccmp(parv[1], "-full") == 0)
    {
      parv++;
      parc--;
      full_etrace = 1;
    }
  }

  if (parc > 1)
  {
    tname = parv[1];

    if (tname != NULL)
      wilds = strchr(tname, '*') || strchr(tname, '?');
    else
      tname = "*";
  }
  else
  {
    do_all = 1;
    tname = "*";
  }

  if (IsFull(source_p))
    full_etrace = 1;

  if (!wilds && !do_all)
  {
    target_p = find_client(tname);

    if (target_p && MyClient(target_p))
      report_this_status(source_p, target_p, full_etrace);

    sendto_one(source_p, form_str(RPL_ENDOFTRACE), me.name,
               source_p->name, tname);
    return;
  }

  DLINK_FOREACH(ptr, local_client_list.head)
  {
    target_p = ptr->data;

    if (wilds)
    {
      if (match(tname, target_p->name))
        report_this_status(source_p, target_p, full_etrace);
    }
    else
      report_this_status(source_p, target_p, full_etrace);
  }

  sendto_one(source_p, form_str(RPL_ENDOFTRACE), me.name,
             source_p->name, tname);
}
