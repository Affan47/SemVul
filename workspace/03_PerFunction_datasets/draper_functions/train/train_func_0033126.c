remove_user_from_channel(aClient *sptr, aChannel *chptr)
{
	Reg	Link	**curr;
	Reg	Link	*tmp, *tmp2;

	for (curr = &chptr->members; (tmp = *curr); curr = &tmp->next)
		if (tmp->value.cptr == sptr)
		    {


			if (tmp->flags & CHFL_CHANOP)
			{
				chptr->reop = timeofday + LDELAYCHASETIMELIMIT +
					myrand() % 300;
			}

			*curr = tmp->next;
			free_link(tmp);
			break;
		    }
	for (curr = &sptr->user->channel; (tmp = *curr); curr = &tmp->next)
		if (tmp->value.chptr == chptr)
		    {
			*curr = tmp->next;
			free_link(tmp);
			break;
		    }
	if (sptr->from)
		tmp2 = find_user_link(chptr->clist, sptr->from);
	else
		tmp2 = find_user_link(chptr->clist, sptr);
	if (tmp2 && !--tmp2->flags)
		for (curr = &chptr->clist; (tmp = *curr); curr = &tmp->next)
			if (tmp2 == tmp)
			    {
				*curr = tmp->next;
				free_link(tmp);
				break;
			    }
	if (!IsQuiet(chptr))
	{
		sptr->user->joined--;
		istat.is_userc--;
	}
#ifdef USE_SERVICES
	if (chptr->users == 1)
		check_services_butone(SERVICE_WANT_CHANNEL|
				      SERVICE_WANT_VCHANNEL, NULL, &me,
				      "CHANNEL %s %d", chptr->chname,
				      chptr->users-1);
	else
		check_services_butone(SERVICE_WANT_VCHANNEL, NULL, &me,
				      "CHANNEL %s %d", chptr->chname,
				      chptr->users-1);
#endif
	if (--chptr->users <= 0)
	    {
		u_int sz = sizeof(aChannel) + strlen(chptr->chname);

		istat.is_chan--;
		istat.is_chanmem -= sz;
		istat.is_hchan++;
		istat.is_hchanmem += sz;
		free_channel(chptr);
	    }
	istat.is_chanusers--;
}
