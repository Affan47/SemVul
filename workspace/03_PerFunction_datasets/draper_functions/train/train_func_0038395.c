gkrellmd_add_mailbox(gchar *path)
	{
	Mailbox	*mbox;

	if (!path || !*path)
		return;
	mbox = g_new0(Mailbox, 1);
	mbox->path = g_strdup(path);
	get_local_mboxtype(mbox);

	if (mbox->mboxtype == MBOX_MAILDIR)
		mbox->check_func = check_maildir;
	else if (mbox->mboxtype == MBOX_MH_DIR)
		mbox->check_func = check_mh_dir;
	else
		mbox->check_func = check_mbox;

	mailbox_list = g_list_append(mailbox_list, mbox);
	gkrellmd_add_serveflag_done(&mbox->changed);
	}
