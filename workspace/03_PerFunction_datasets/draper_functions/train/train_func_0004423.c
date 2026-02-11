channel_modes(struct Channel *chptr, struct Client *client_p)
{
	static char buf[BUFSIZE];
	char *mbuf = buf;

	*mbuf++ = '+';

	if(chptr->mode.mode & MODE_SECRET)
		*mbuf++ = 's';
	if(chptr->mode.mode & MODE_PRIVATE)
		*mbuf++ = 'p';
	if(chptr->mode.mode & MODE_MODERATED)
		*mbuf++ = 'm';
	if(chptr->mode.mode & MODE_TOPICLIMIT)
		*mbuf++ = 't';
	if(chptr->mode.mode & MODE_INVITEONLY)
		*mbuf++ = 'i';
	if(chptr->mode.mode & MODE_NOPRIVMSGS)
		*mbuf++ = 'n';
#ifdef ENABLE_SERVICES
	if(chptr->mode.mode & MODE_REGONLY)
		*mbuf++ = 'r';
#endif
	if(chptr->mode.mode & MODE_SSLONLY)
		*mbuf++ = 'S';

	if(chptr->mode.limit && *chptr->mode.key)
	{
		if(IsMe(client_p) || !MyClient(client_p) || IsMember(client_p, chptr))
			rb_sprintf(mbuf, "lk %d %s", chptr->mode.limit, chptr->mode.key);
		else
			strcpy(mbuf, "lk");
	}
	else if(chptr->mode.limit)
	{
		if(IsMe(client_p) || !MyClient(client_p) || IsMember(client_p, chptr))
			rb_sprintf(mbuf, "l %d", chptr->mode.limit);
		else
			strcpy(mbuf, "l");
	}
	else if(*chptr->mode.key)
	{
		if(IsMe(client_p) || !MyClient(client_p) || IsMember(client_p, chptr))
			rb_sprintf(mbuf, "k %s", chptr->mode.key);
		else
			strcpy(mbuf, "k");
	}
	else
		*mbuf = '\0';

	return buf;
}
