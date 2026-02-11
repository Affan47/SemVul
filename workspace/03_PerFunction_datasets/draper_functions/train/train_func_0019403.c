get_sendq(struct Client *client_p)
{
  unsigned int sendq = DEFAULT_SENDQ;
  dlink_node *ptr;
  struct ConfItem *conf;
  struct ConfItem *class_conf;
  struct ClassItem *aclass;
  struct AccessItem *aconf;

  if (client_p && !IsMe(client_p) && (client_p->localClient->confs.head))
  {
    DLINK_FOREACH(ptr, client_p->localClient->confs.head)
    {
      conf = ptr->data;
      if ((conf->type == SERVER_TYPE) || (conf->type == OPER_TYPE)
	  || (conf->type == CLIENT_TYPE))
      {
	aconf = (struct AccessItem *)map_to_conf(conf);
	if ((class_conf = aconf->class_ptr) == NULL)
	  continue;
	aclass = (struct ClassItem *)map_to_conf(class_conf);
	sendq = MaxSendq(aclass);
	return sendq;
      }
    }
  }


  return DEFAULT_SENDQ;
}
