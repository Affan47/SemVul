conf_set_listen_port_both(confentry_t * entry, conf_t * conf, struct conf_items *item, int ssl)
{
	rb_dlink_node *ptr;
	confentry_t *xentry;
	int family = AF_INET;

	RB_DLINK_FOREACH(ptr, entry->flist.head)
	{
		xentry = ptr->data;
		if(listener_address == NULL)
		{
#ifdef RB_IPV6
			if(listener_aftype > 0)
				family = listener_aftype;
#endif
			add_listener(xentry->number, listener_address, family, ssl);
		}
		else
		{
#ifdef RB_IPV6
			if(listener_aftype <= 0 && strchr(listener_address, ':') != NULL)
				family = AF_INET6;
#endif
			add_listener(xentry->number, listener_address, family, ssl);
		}
	}
}
