dcc_abort (session *sess, struct DCC *dcc)
{
	if (dcc)
	{
		switch (dcc->dccstat)
		{
		case STAT_QUEUED:
		case STAT_CONNECTING:
		case STAT_ACTIVE:
			dcc_close (dcc, STAT_ABORTED, FALSE);
			switch (dcc->type)
			{
			case TYPE_CHATSEND:
			case TYPE_CHATRECV:
				EMIT_SIGNAL (XP_TE_DCCCHATABORT, sess, dcc->nick, NULL, NULL,
								 NULL, 0);
				break;
			case TYPE_SEND:
				EMIT_SIGNAL (XP_TE_DCCSENDABORT, sess, dcc->nick,
								 file_part (dcc->file), NULL, NULL, 0);
				break;
			case TYPE_RECV:
				EMIT_SIGNAL (XP_TE_DCCRECVABORT, sess, dcc->nick,
								 dcc->file, NULL, NULL, 0);
			}
			break;
		default:
			dcc_close (dcc, 0, TRUE);
		}
	}
}
