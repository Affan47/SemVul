server_exists(const char *servername)
{
	struct Client *target_p;
	rb_dlink_node *ptr;

	RB_DLINK_FOREACH(ptr, global_serv_list.head)
	{
		target_p = ptr->data;

		if(match(target_p->name, servername) || match(servername, target_p->name))
			return target_p;
	}

	return NULL;
}
