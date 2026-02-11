get_channel(aClient *cptr, char *chname, int flag)
{
	Reg	aChannel *chptr;
	int	len;

	if (BadPtr(chname))
		return NULL;

	len = strlen(chname);
	if (MyClient(cptr) && len > CHANNELLEN)
	{
		len = CHANNELLEN;
		*(chname+CHANNELLEN) = '\0';
#ifdef JAPANESE
#if 0


		if (check_channelmask(cptr, cptr, chname) == -1)
			return NULL;
#endif
#endif
	}
	if ((chptr = find_channel(chname, (aChannel *)NULL)))
		return (chptr);
	if (flag == CREATE)
	    {
		chptr = (aChannel *)MyMalloc(sizeof(aChannel) + len);
		bzero((char *)chptr, sizeof(aChannel));
		strncpyzt(chptr->chname, chname, len+1);
		if (channel)
			channel->prevch = chptr;
		chptr->prevch = NULL;
		chptr->nextch = channel;
		chptr->history = 0;
#ifdef JAPANESE
		chptr->flags = 0;
		if (jp_chname(chname))
			chptr->flags = FLAGS_JP;
#endif
		channel = chptr;
		(void)add_to_channel_hash_table(chname, chptr);
	    }
	return chptr;
}
