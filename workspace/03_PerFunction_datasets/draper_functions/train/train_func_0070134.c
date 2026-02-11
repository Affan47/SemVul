AddAccessChannel(struct NickInfo *nptr, struct ChanInfo *chanptr,
							 struct ChanAccess *accessptr)

{
	struct AccessChannel *acptr;

	for (acptr = nptr->AccessChannels; acptr != NULL; acptr = acptr->next)
	{
		if (acptr->cptr == chanptr)
		{
			if (acptr->accessptr->level < accessptr->level)
				acptr->accessptr->level = accessptr->level;

			return NULL;
		}
	}

	acptr = MyMalloc(sizeof(struct AccessChannel));
	acptr->cptr = chanptr;
	acptr->accessptr = accessptr;

	acptr->prev = NULL;
	acptr->next = nptr->AccessChannels;
	if (acptr->next)
		acptr->next->prev = acptr;
	nptr->AccessChannels = acptr;

	return (acptr);
}
