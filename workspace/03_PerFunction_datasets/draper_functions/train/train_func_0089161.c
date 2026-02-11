mo_xline(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	struct ConfItem *aconf;
	const char *name;
	const char *reason;
	const char *target_server = NULL;
	int temp_time;
	int loc = 1;
	int propagated = ConfigFileEntry.use_propagated_bans;

	if(!IsOperXline(source_p))
	{
		sendto_one(source_p, form_str(ERR_NOPRIVS), me.name, source_p->name, "xline");
		return 0;
	}

	if((temp_time = valid_temp_time(parv[loc])) >= 0)
		loc++;

	else
		temp_time = 0;

	name = parv[loc];
	loc++;


	if(parc >= loc + 2 && !irccmp(parv[loc], "ON"))
	{
		if(!IsOperRemoteBan(source_p))
		{
			sendto_one(source_p, form_str(ERR_NOPRIVS),
				   me.name, source_p->name, "remoteban");
			return 0;
		}

		target_server = parv[loc + 1];
		loc += 2;
	}

	if(parc <= loc || EmptyString(parv[loc]))
	{
		sendto_one(source_p, form_str(ERR_NEEDMOREPARAMS),
			   me.name, source_p->name, "XLINE");
		return 0;
	}

	reason = parv[loc];

	if(target_server != NULL)
	{
		propagate_xline(source_p, target_server, temp_time, name, "2", reason);

		if(!match(target_server, me.name))
			return 0;


		propagated = 0;
	}
	else if(!propagated && rb_dlink_list_length(&cluster_conf_list) > 0)
		cluster_xline(source_p, temp_time, name, reason);

	if((aconf = find_xline_mask(name)) != NULL)
	{
		sendto_one(source_p, ":%s NOTICE %s :[%s] already X-Lined by [%s] - %s",
			   me.name, source_p->name, name, aconf->host, aconf->passwd);
		return 0;
	}

	if(!valid_xline(source_p, name, reason))
		return 0;

	if(propagated && temp_time == 0)
	{
		sendto_one_notice(source_p, ":Cannot set a permanent global ban");
		return 0;
	}

	apply_xline(source_p, name, reason, temp_time, propagated);

	return 0;
}
