mo_dline(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	char def[] = "No Reason";
	const char *dlhost;
	char *reason = def;
	char cidr_form_host[HOSTLEN + 1];
	int tdline_time = 0;
	const char *target_server = NULL;
	int loc = 1;

	if(!IsOperK(source_p))
	{
		sendto_one(source_p, form_str(ERR_NOPRIVS), me.name, source_p->name, "kline");
		return 0;
	}

	if((tdline_time = valid_temp_time(parv[loc])) >= 0)
		loc++;

	dlhost = parv[loc];
	rb_strlcpy(cidr_form_host, dlhost, sizeof(cidr_form_host));
	loc++;


	if (*dlhost == ':')
	{
		sendto_one_notice(source_p, ":Invalid D-Line");
		return 0;
	}

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

	if(parc >= loc + 1 && !EmptyString(parv[loc]))
		reason = LOCAL_COPY(parv[loc]);

	if(target_server != NULL)
	{
		sendto_match_servs(source_p, target_server,
				   CAP_ENCAP, NOCAPS,
				   "ENCAP %s DLINE %d %s :%s",
				   target_server, tdline_time, dlhost, reason);

		if(!match(target_server, me.name))
			return 0;
	}

	apply_dline(source_p, dlhost, tdline_time, reason);

	check_dlines();
	return 0;
}
