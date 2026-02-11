update_mail(GkrellmdMonitor *mon, gboolean force)
	{
	Mailbox		*mbox;
	GList		*list;
	static gint	second_count;

	if (   (!GK.second_tick || (++second_count % mail_check_timeout) != 0)
		&& !force
	   )
		return;

	for (list = mailbox_list; list; list = list->next)
		{
		mbox = (Mailbox *) list->data;
		if (mbox->check_func)
			(*mbox->check_func)(mbox);

		if (   mbox->prev_mail_count != mbox->mail_count
			|| mbox->prev_new_mail_count != mbox->new_mail_count
		   )
			{
			mbox->changed = TRUE;
			mail_need_serve = TRUE;
			gkrellmd_need_serve(mon);
			}
		mbox->prev_mail_count = mbox->mail_count;
		mbox->prev_new_mail_count = mbox->new_mail_count;
		}
	}
