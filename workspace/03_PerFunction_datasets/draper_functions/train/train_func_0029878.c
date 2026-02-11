inc_recv_message(Session *session, const gchar *msg, gpointer data)
{
	IncSession *inc_session = (IncSession *)data;
	IncProgressDialog *inc_dialog;

	cm_return_val_if_fail(inc_session != NULL, -1);

	inc_dialog = (IncProgressDialog *)inc_session->data;

	switch (POP3_SESSION(session)->state) {
	case POP3_GETAUTH_USER:
	case POP3_GETAUTH_PASS:
	case POP3_GETAUTH_APOP:
	case POP3_GETRANGE_STAT:
	case POP3_GETRANGE_LAST:
	case POP3_GETRANGE_UIDL:
	case POP3_GETSIZE_LIST:
		inc_progress_dialog_update(inc_dialog, inc_session);
		break;
	case POP3_RETR:
		inc_recv_data_progressive(session, 0, 0, inc_session);
		break;
	case POP3_LOGOUT:
		inc_progress_dialog_update(inc_dialog, inc_session);
		break;
	default:
		break;
	}

	return 0;
}
