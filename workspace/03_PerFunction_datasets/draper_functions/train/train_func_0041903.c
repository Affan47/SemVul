ms_pong(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	struct Client *target_p;
	const char *destination;

	destination = parv[2];
	source_p->flags &= ~FLAGS_PINGSENT;


	if(!EmptyString(destination) && !match(destination, me.name) && irccmp(destination, me.id))
	{
		if((target_p = find_client(destination)) ||
		   (target_p = find_server(NULL, destination)))
			sendto_one(target_p, ":%s PONG %s %s",
				   get_id(source_p, target_p), parv[1], get_id(target_p, target_p));
		else
		{
			if(!IsDigit(*destination))
				sendto_one_numeric(source_p, ERR_NOSUCHSERVER,
						   form_str(ERR_NOSUCHSERVER), destination);
			return 0;
		}
	}


	if(IsServer(source_p) && !HasSentEob(source_p))
	{
		if(MyConnect(source_p))
			sendto_realops_flags(UMODE_ALL, L_ALL,
					     "End of burst (emulated) from %s (%d seconds)",
					     source_p->name,
					     (signed int)(rb_current_time() -
							  source_p->localClient->firsttime));
		SetEob(source_p);
		eob_count++;
	}

	return 0;
}
