rebuild_cidr_list(int aftype, struct ConfItem *oldcl, struct ClassItem *newcl,
                  dlink_list *old_list, dlink_list *new_list, int changed)
{
  dlink_node *ptr;
  struct Client *client_p;
  struct ConfItem *conf;
  struct AccessItem *aconf;

  if (!changed)
  {
    *new_list = *old_list;
    old_list->head = old_list->tail = NULL;
    old_list->length = 0;
    return;
  }

  DLINK_FOREACH(ptr, local_client_list.head)
  {
    client_p = ptr->data;
    if (client_p->localClient->aftype != aftype)
      continue;
    if (dlink_list_length(&client_p->localClient->confs) == 0)
      continue;

    conf = client_p->localClient->confs.tail->data;
    if (conf->type == CLIENT_TYPE)
    {
      aconf = map_to_conf(conf);
      if (aconf->class_ptr == oldcl)
        cidr_limit_reached(1, &client_p->localClient->ip, newcl);
    }
  }
}
