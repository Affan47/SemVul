list_accepts(struct Client *source_p)
{
	rb_dlink_node *ptr;
	struct Client *target_p;
	char nicks[BUFSIZE];
	int len = 0;
	int len2 = 0;
	int count = 0;

	*nicks = '\0';
	len2 = strlen(source_p->name) + 10;

	RB_DLINK_FOREACH(ptr, source_p->localClient->allow_list.head)
	{
		target_p = ptr->data;

		if(target_p)
		{

			if((len + strlen(target_p->name) + len2 > BUFSIZE) || count > 14)
			{
				sendto_one(source_p, form_str(RPL_ACCEPTLIST),
					   me.name, source_p->name, nicks);

				len = count = 0;
				*nicks = '\0';
			}

			len += rb_snprintf(nicks + len, sizeof(nicks) - len, "%s ", target_p->name);
			count++;
		}
	}

	if(*nicks)
		sendto_one(source_p, form_str(RPL_ACCEPTLIST),
			   me.name, source_p->name, nicks);

	sendto_one(source_p, form_str(RPL_ENDOFACCEPT),
		   me.name, source_p->name);

}
