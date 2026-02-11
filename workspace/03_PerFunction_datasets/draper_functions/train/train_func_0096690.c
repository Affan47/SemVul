inc_account_mail_real(MainWindow *mainwin, PrefsAccount *account)
{
	IncProgressDialog *inc_dialog;
	IncSession *session;

	switch (account->protocol) {
	case A_IMAP4:
	case A_NNTP:


		folderview_check_new(FOLDER(account->folder));
		return 0;
	case A_POP3:
	case A_APOP:
		session = inc_session_new(account);
		if (!session) return 0;

		inc_dialog = inc_progress_dialog_create(FALSE);
		inc_dialog->queue_list = g_list_append(inc_dialog->queue_list,
						       session);
		inc_dialog->mainwin = mainwin;
		inc_progress_dialog_set_list(inc_dialog);

		if (mainwin) {
			toolbar_main_set_sensitive(mainwin);
			main_window_set_menu_sensitive(mainwin);
		}

		return inc_start(inc_dialog);

	case A_LOCAL:
		return inc_spool_account(account);

	default:
		break;
	}
	return 0;
}
