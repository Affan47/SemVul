mo_chantrace(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	struct Client *target_p;
	struct Channel *chptr;
	struct membership *msptr;
	const char *sockhost;
	const char *name;
	rb_dlink_node *ptr;
	int operspy = 0;

	name = parv[1];

	if(IsOperSpy(source_p) && parv[1][0] == '!')
	{
		name++;
		operspy = 1;
		if(EmptyString(name))
		{
			sendto_one_numeric(source_p, ERR_NEEDMOREPARAMS,
					   form_str(ERR_NEEDMOREPARAMS), me.name, source_p->name,
					   "CHANTRACE");
			return 0;
		}
	}

	if((chptr = find_channel(name)) == NULL)
	{
		sendto_one_numeric(source_p, ERR_NOSUCHCHANNEL, form_str(ERR_NOSUCHCHANNEL), name);
		return 0;
	}


	if(operspy)
		report_operspy(source_p, "CHANTRACE", chptr->chname);

	if(!operspy && !IsMember(client_p, chptr))
	{
		sendto_one_numeric(source_p, ERR_NOTONCHANNEL, form_str(ERR_NOTONCHANNEL),
				   chptr->chname);
		return 0;
	}
	SetCork(source_p);
	RB_DLINK_FOREACH(ptr, chptr->members.head)
	{
		msptr = ptr->data;
		target_p = msptr->client_p;

		if(EmptyString(target_p->sockhost))
			sockhost = empty_sockhost;
		else if(!show_ip(source_p, target_p))
			sockhost = spoofed_sockhost;
		else
			sockhost = target_p->sockhost;

		sendto_one(source_p, form_str(RPL_ETRACE),
			   me.name, source_p->name, IsOper(target_p) ? "Oper" : "User",

			   target_p->servptr->name,
			   target_p->name, target_p->username, target_p->host,
			   sockhost, target_p->info);
	}
	ClearCork(source_p);
	sendto_one_numeric(source_p, RPL_ENDOFTRACE, form_str(RPL_ENDOFTRACE), me.name);
	return 0;
}
