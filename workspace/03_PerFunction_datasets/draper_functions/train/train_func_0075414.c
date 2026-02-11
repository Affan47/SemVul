m_unregistered(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{


	if(client_p->localClient->number_of_nick_changes == 0)
	{
		sendto_one(client_p, form_str(ERR_NOTREGISTERED), me.name);
		client_p->localClient->number_of_nick_changes++;
	}

	return 0;
}
