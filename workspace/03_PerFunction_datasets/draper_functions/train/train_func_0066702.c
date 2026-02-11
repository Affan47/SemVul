dcc_check_timeouts (void)
{
	struct DCC *dcc;
	time_t tim = time (0);
	GSList *next, *list = dcc_list;

	while (list)
	{
		dcc = (struct DCC *) list->data;
		next = list->next;

		switch (dcc->dccstat)
		{
		case STAT_ACTIVE:
			dcc_calc_cps (dcc);
			fe_dcc_update (dcc);

			if (dcc->type == TYPE_SEND || dcc->type == TYPE_RECV)
			{
				if (prefs.hex_dcc_stall_timeout > 0)
				{
					if (!dcc->throttled
						&& tim - dcc->lasttime > prefs.hex_dcc_stall_timeout)
					{
						EMIT_SIGNAL (XP_TE_DCCSTALL, dcc->serv->front_session,
										 dcctypes[dcc->type],
										 file_part (dcc->file), dcc->nick, NULL, 0);
						dcc_close (dcc, STAT_ABORTED, FALSE);
					}
				}
			}
			break;
		case STAT_QUEUED:
			if (dcc->type == TYPE_SEND || dcc->type == TYPE_CHATSEND)
			{
				if (tim - dcc->offertime > prefs.hex_dcc_timeout)
				{
					if (prefs.hex_dcc_timeout > 0)
					{
						EMIT_SIGNAL (XP_TE_DCCTOUT, dcc->serv->front_session,
										 dcctypes[dcc->type],
										 file_part (dcc->file), dcc->nick, NULL, 0);
						dcc_close (dcc, STAT_ABORTED, FALSE);
					}
				}
			}
			break;
		case STAT_DONE:
		case STAT_FAILED:
		case STAT_ABORTED:
			if (prefs.hex_dcc_remove)
				dcc_close (dcc, 0, TRUE);
			break;
		}
		list = next;
	}
}
