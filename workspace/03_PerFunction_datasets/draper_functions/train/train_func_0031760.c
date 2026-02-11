doretr(const char *eventid)
{
	struct PCP *pcp;
	struct PCP_retr r;
	struct xretrinfo xr;
	const char *event_id_array[2];
	struct xretr_time_list *tl;
	struct xretr_participant_list *pl;

	pcp=open_calendar();

	memset(&r, 0, sizeof(r));
	memset(&xr, 0, sizeof(xr));

	r.callback_arg= &xr;
	r.callback_retr_status=doretr_status;
	r.callback_retr_date=doretr_date;
	r.callback_retr_participants=doretr_participants;

	event_id_array[0]=eventid;
	event_id_array[1]=NULL;

	r.event_id_list=event_id_array;

	if (pcp_retr(pcp, &r) == 0)
	{
		r.callback_retr_status=NULL;
		r.callback_retr_date=NULL;
		r.callback_retr_participants=NULL;

		r.callback_begin_func=doretr_begin;
		r.callback_rfc822_func=doretr_save;
		r.callback_end_func=do_show_retr;
		if (pcp_retr(pcp, &r) == 0)
		{
			pcp_close(pcp);
		}
		else
		{
			error(pcp, r.errcode, "pcp_retr");
			pcp_close(pcp);
		}
	}
	else
	{
		error(pcp, r.errcode, "pcp_retr");
		pcp_close(pcp);
	}

	while ((pl=xr.participant_list) != NULL)
	{
		xr.participant_list=pl->next;
		free(pl->participant);
		free(pl);
	}

	while ((tl=xr.time_list) != NULL)
	{
		xr.time_list=tl->next;
		free(tl);
	}
}
