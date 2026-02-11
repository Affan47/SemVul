mo_testmask(struct Client *client_p, struct Client *source_p,
                        int parc, const char *parv[])
{
	struct Client *target_p;
	int lcount = 0;
	int gcount = 0;
	char *name, *username, *hostname;
	const char *sockhost;
	char *gecos = NULL;
	rb_dlink_node *ptr;

	name = LOCAL_COPY(parv[1]);
	collapse(name);


	if((hostname = strchr(name, '@')) == NULL)
	{
		sendto_one_notice(source_p, ":Invalid parameters");
		return 0;
	}

	*hostname++ = '\0';


	if((username = strchr(name, '!')) == NULL)
	{
		username = name;
		name = NULL;
	}
	else
		*username++ = '\0';

	if(EmptyString(username) || EmptyString(hostname))
	{
		sendto_one_notice(source_p, ":Invalid parameters");
		return 0;
	}

	if(parc > 2 && !EmptyString(parv[2]))
	{
		gecos = LOCAL_COPY(parv[2]);
		collapse_esc(gecos);
	}

	RB_DLINK_FOREACH(ptr, global_client_list.head)
	{
		target_p = ptr->data;

		if(!IsPerson(target_p))
			continue;

		if(EmptyString(target_p->sockhost))
			sockhost = empty_sockhost;
		else if(!show_ip(source_p, target_p))
			sockhost = spoofed_sockhost;
		else
			sockhost = target_p->sockhost;

		if(match(username, target_p->username) &&
		   (match(hostname, target_p->host) ||
		    match(hostname, target_p->orighost) ||
		    match(hostname, sockhost) || match_ips(hostname, sockhost)))
		{
			if(name && !match(name, target_p->name))
				continue;

			if(gecos && !match_esc(gecos, target_p->info))
				continue;

			if(MyClient(target_p))
				lcount++;
			else
				gcount++;
		}
	}

	sendto_one(source_p, form_str(RPL_TESTMASKGECOS),
			me.name, source_p->name,
			lcount, gcount, name ? name : "*",
			username, hostname, gecos ? gecos : "*");
	return 0;
}
