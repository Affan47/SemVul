free_channel(aChannel *chptr)
{
	Reg	Link *tmp;
	Link	*obtmp;
	int	len = sizeof(aChannel) + strlen(chptr->chname), now = 0;

        if (chptr->history == 0 || timeofday >= chptr->history)

		now = 1;

	if (*chptr->chname != '!' || now)
	    {
		while ((tmp = chptr->invites))
			del_invite(tmp->value.cptr, chptr);

		tmp = chptr->mlist;
		while (tmp)
		    {
			obtmp = tmp;
			tmp = tmp->next;
			istat.is_banmem -= BanLen(obtmp->value.alist);
			istat.is_bans--;
			free_bei(obtmp->value.alist);
			free_link(obtmp);
		    }
		chptr->mlist = NULL;
	    }

	if (now)
	    {
		istat.is_hchan--;
		istat.is_hchanmem -= len;
		if (chptr->prevch)
			chptr->prevch->nextch = chptr->nextch;
		else
			channel = chptr->nextch;
		if (chptr->nextch)
			chptr->nextch->prevch = chptr->prevch;
		del_from_channel_hash_table(chptr->chname, chptr);

		if (*chptr->chname == '!' && close_chid(chptr->chname+1))
			cache_chid(chptr);
		else
			MyFree(chptr);
	    }
}
