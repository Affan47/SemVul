find_is_glined(const char *host, const char *user)
{
	struct ConfItem *aconf;
	rb_dlink_node *ptr;

	RB_DLINK_FOREACH(ptr, glines.head)
	{
		aconf = ptr->data;
		if((!user || irccmp(aconf->user, user) == 0) &&
		   (!host || irccmp(aconf->host, host) == 0))
			return aconf;
	}

	return NULL;
}
