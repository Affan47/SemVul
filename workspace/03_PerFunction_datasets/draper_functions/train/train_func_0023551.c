mr_nick(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	struct Client *target_p;
	char nick[NICKLEN];
	char *s;

	if(parc < 2 || EmptyString(parv[1]) || (parv[1][0] == '~'))
	{
		sendto_one(source_p, form_str(ERR_NONICKNAMEGIVEN),
			   me.name, EmptyString(source_p->name) ? "*" : source_p->name);
		return 0;
	}


	if((s = strchr(parv[1], '~')))
		*s = '\0';


	rb_strlcpy(nick, parv[1], sizeof(nick));


	if(!clean_nick(nick, 1))
	{
		sendto_one(source_p, form_str(ERR_ERRONEUSNICKNAME),
			   me.name, EmptyString(parv[0]) ? "*" : parv[0], parv[1]);
		return 0;
	}


	if(!IsExemptResv(source_p) && find_nick_resv(nick))
	{
		sendto_one(source_p, form_str(ERR_ERRONEUSNICKNAME),
			   me.name, EmptyString(source_p->name) ? "*" : source_p->name, nick);
		return 0;
	}

	if(hash_find_nd(nick))
	{
		sendto_one(source_p, form_str(ERR_UNAVAILRESOURCE),
			   me.name, EmptyString(source_p->name) ? "*" : source_p->name, nick);
		return 0;
	}

	if((target_p = find_client(nick)) == NULL)
		set_initial_nick(client_p, source_p, nick);
	else if(source_p == target_p)
		strcpy(source_p->user->name, nick);
	else
		sendto_one(source_p, form_str(ERR_NICKNAMEINUSE), me.name, "*", nick);

	return 0;
}
