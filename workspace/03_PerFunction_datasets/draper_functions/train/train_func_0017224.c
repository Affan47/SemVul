safelist_channel_named(struct Client *source_p, const char *name, int operspy)
{
	struct Channel *chptr;
	char *p;
	int visible;

	sendto_one(source_p, form_str(RPL_LISTSTART), me.name, source_p->name);

	if ((p = strchr(name, ',')))
		*p = '\0';

	if (*name == '\0')
	{
		sendto_one_numeric(source_p, ERR_NOSUCHNICK, form_str(ERR_NOSUCHNICK), name);
		sendto_one(source_p, form_str(RPL_LISTEND), me.name, source_p->name);
		return;
	}

	chptr = find_channel(name);

	if (chptr == NULL)
	{
		sendto_one_numeric(source_p, ERR_NOSUCHNICK, form_str(ERR_NOSUCHNICK), name);
		sendto_one(source_p, form_str(RPL_LISTEND), me.name, source_p->name);
		return;
	}

	visible = !SecretChannel(chptr) || IsMember(source_p, chptr);
	if (visible || operspy)
		sendto_one(source_p, form_str(RPL_LIST), me.name, source_p->name,
			   visible ? "" : "!",
			   chptr->chname, rb_dlink_list_length(&chptr->members),
			   chptr->topic == NULL ? "" : chptr->topic);

	sendto_one(source_p, form_str(RPL_LISTEND), me.name, source_p->name);
	return;
}
