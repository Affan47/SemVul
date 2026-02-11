m_whois(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	static time_t last_used = 0;

	if(parc > 2)
	{
		if(EmptyString(parv[2]))
		{
			sendto_one(source_p, form_str(ERR_NONICKNAMEGIVEN),
					me.name, source_p->name);
			return 0;
		}

		if(!IsOper(source_p))
		{

			if((last_used + ConfigFileEntry.pace_wait_simple) > rb_current_time() || !ratelimit_client(source_p, 2))
			{
				sendto_one(source_p, form_str(RPL_LOAD2HI),
					   me.name, source_p->name, "WHOIS");
				sendto_one_numeric(source_p, RPL_ENDOFWHOIS,
						   form_str(RPL_ENDOFWHOIS), parv[2]);
				return 0;
			}
			else
				last_used = rb_current_time();
		}

		if(hunt_server(client_p, source_p, ":%s WHOIS %s :%s", 1, parc, parv) !=
		   HUNTED_ISME)
			return 0;

		parv[1] = parv[2];

	}
	do_whois(client_p, source_p, parc, parv);

	return 0;
}
