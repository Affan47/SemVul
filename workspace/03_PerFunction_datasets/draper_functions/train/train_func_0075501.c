exit_one_client(struct Client *source_p, const char *quitmsg)
{
  dlink_node *lp = NULL, *next_lp = NULL;

  assert(!IsMe(source_p));

  if (IsClient(source_p))
  {
    if (source_p->servptr->serv != NULL)
      dlinkDelete(&source_p->lnode, &source_p->servptr->serv->client_list);


    sendto_common_channels_local(source_p, 0, ":%s!%s@%s QUIT :%s",
                                 source_p->name, source_p->username,
                                 source_p->host, quitmsg);
    DLINK_FOREACH_SAFE(lp, next_lp, source_p->channel.head)
      remove_user_from_channel(lp->data);

    add_history(source_p, 0);
    off_history(source_p);

    watch_check_hash(source_p, RPL_LOGOFF);

    if (MyConnect(source_p))
    {

      DLINK_FOREACH_SAFE(lp, next_lp, source_p->localClient->invited.head)
        del_invite(lp->data, source_p);

      del_all_accepts(source_p);
    }
  }
  else if (IsServer(source_p))
  {
    dlinkDelete(&source_p->lnode, &source_p->servptr->serv->server_list);

    if ((lp = dlinkFindDelete(&global_serv_list, source_p)) != NULL)
      free_dlink_node(lp);
  }


  if (HasID(source_p))
    hash_del_id(source_p);
  if (source_p->name[0])
    hash_del_client(source_p);

  if (IsUserHostIp(source_p))
    delete_user_host(source_p->username, source_p->host, !MyConnect(source_p));


  if (source_p != NULL && source_p->node.next != NULL)
    dlinkDelete(&source_p->node, &global_client_list);

  update_client_exit_stats(source_p);


  assert(dlinkFind(&dead_list, source_p) == NULL);


  SetDead(source_p);
  dlinkAdd(source_p, make_dlink_node(), &dead_list);
}
