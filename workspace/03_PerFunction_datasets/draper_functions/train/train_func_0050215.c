doing_stats_hook(hook_data_int *hdata)
{
	rb_dlink_node	*ptr;
	hurt_t		*hurt;
	struct Client	*source_p;

	s_assert(hdata);
	s_assert(hdata->client);

	source_p = hdata->client;
	if(hdata->arg2 != (int) 's')
		return;
	if((ConfigFileEntry.stats_k_oper_only == 2) && !IsOper(source_p))
		return;
	if ((ConfigFileEntry.stats_k_oper_only == 1) && !IsOper(source_p))
	{
		hurt = hurt_find(source_p->sockhost);
		if (hurt != NULL)
		{
			sendto_one_numeric(source_p, RPL_STATSKLINE,
					form_str(RPL_STATSKLINE), 's',
					"*", hurt->ip, hurt->reason, "", "");
			return;
		}

		hurt = hurt_find(source_p->orighost);
		if (hurt != NULL)
		{
			sendto_one_numeric(source_p, RPL_STATSKLINE,
					form_str(RPL_STATSKLINE), 's',
					"*", hurt->ip, hurt->reason, "", "");
			return;
		}
		return;
	}

	RB_DLINK_FOREACH(ptr, hurt_confs.head)
	{
		hurt = (hurt_t *) ptr->data;
		sendto_one_numeric(source_p, RPL_STATSKLINE,
				form_str(RPL_STATSKLINE), 's',
				"*", hurt->ip, hurt->reason, "", "");
	}
}
