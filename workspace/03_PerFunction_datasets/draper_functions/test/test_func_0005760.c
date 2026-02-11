DeleteChannel(struct Channel *cptr)
{
	struct ChannelUser *cnext = NULL;
	struct ChannelBan *bnext = NULL;
	struct Exception *enext = NULL;
#ifdef GECOSBANS

	struct ChannelGecosBan *gnext = NULL;
#endif
#ifdef HYBRID7

	struct InviteException *inext = NULL;
#endif

	if (cptr == NULL)
		return;

	HashDelChan(cptr);


	while (cptr->firstuser != NULL)
	{
		cnext = cptr->firstuser->next;
		MyFree(cptr->firstuser);
		cptr->firstuser = cnext;
	}


	while (cptr->firstban != NULL)
	{
		bnext = cptr->firstban->next;
		MyFree(cptr->firstban->who);
		MyFree(cptr->firstban->mask);
		MyFree(cptr->firstban);
		cptr->firstban = bnext;
	}

#ifdef GECOSBANS

	while (cptr->firstgecosban != NULL)
	{
		gnext = cptr->firstgecosban->next;
		MyFree(cptr->firstgecosban->who);
		MyFree(cptr->firstgecosban->mask);
		MyFree(cptr->firstgecosban);
		cptr->firstgecosban = gnext;
	}
#endif


	while (cptr->exceptlist != NULL)
	{
		enext = cptr->exceptlist->next;
		MyFree(cptr->exceptlist->who);
		MyFree(cptr->exceptlist->mask);
		MyFree(cptr->exceptlist);
		cptr->exceptlist = enext;
	}

#ifdef HYBRID7

	while (cptr->inviteexceptlist != NULL)
	{
		inext = cptr->inviteexceptlist->next;
		MyFree(cptr->inviteexceptlist->who);
		MyFree(cptr->inviteexceptlist->mask);
		MyFree(cptr->inviteexceptlist);
		cptr->inviteexceptlist = inext;
	}
#endif

#ifndef BLOCK_ALLOCATION
	MyFree(cptr->name);
	MyFree(cptr->key);
#ifdef DANCER

	MyFree(cptr->forward);
#endif
#endif

	if (cptr->prev != NULL)
		cptr->prev->next = cptr->next;
	else
		ChannelList = cptr->next;

	if (cptr->next != NULL)
		cptr->next->prev = cptr->prev;

#ifdef BLOCK_ALLOCATION

	BlockSubFree(ChannelHeap, cptr);

#else

	MyFree(cptr);

#endif

	--Network->TotalChannels;
}
