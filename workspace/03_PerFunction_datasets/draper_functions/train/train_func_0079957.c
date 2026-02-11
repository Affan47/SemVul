ms_mode(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	struct Channel *chptr;

	chptr = find_channel(parv[1]);

	if(chptr == NULL)
	{
		sendto_one_numeric(source_p, ERR_NOSUCHCHANNEL,
				   form_str(ERR_NOSUCHCHANNEL), parv[1]);
		return 0;
	}

	set_channel_mode(client_p, source_p, chptr, NULL, parc - 2, parv + 2);

	return 0;
}
