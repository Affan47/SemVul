del_invite(struct Channel *chptr, struct Client *who)
{
  dlink_node *ptr = NULL;

  if ((ptr = dlinkFindDelete(&who->localClient->invited, chptr)))
    free_dlink_node(ptr);

  if ((ptr = dlinkFindDelete(&chptr->invites, who)))
    free_dlink_node(ptr);
}
