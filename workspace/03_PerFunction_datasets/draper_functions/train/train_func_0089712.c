sylpheed_mark_new_count(Mailbox *mbox)
	{
	FILE	*f;
	gchar	*path;
	gint	msgnum, flags, ver, mark_files = 0;

	path = g_strconcat(mbox->path, G_DIR_SEPARATOR_S,
				".sylpheed_mark", NULL);
	f = fopen(path, "rb");
	g_free(path);
	if (!f)
		return FALSE;

	if (   fread(&ver, sizeof(ver), 1, f) == 1
		&& SYLPHEED_MARK_VERSION == ver
	   )
		{
		while (   fread(&msgnum, sizeof(msgnum), 1, f) == 1
			   && fread(&flags, sizeof(flags), 1, f) == 1
			  )
			{
			if (   (flags & SYLPHEED_MSG_NEW)
				|| ((flags & SYLPHEED_MSG_UNREAD) && unseen_is_new)
			   )
				mbox->new_mail_count += 1;
			++mark_files;
			}
		if (mark_files < mbox->mail_count)
			mbox->new_mail_count += mbox->mail_count - mark_files;
		}
	fclose(f);
	return TRUE;
	}
