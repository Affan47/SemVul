catch_status(GPid pid, gint status, gpointer data)
{
	ChildInfo *child_info = (ChildInfo *)data;

	debug_print("Child returned %d\n", status);

	childinfo_close_pipes(child_info);
	g_spawn_close_pid(child_info->pid);
	child_info->pid = 0;

	if (child_info->children->action_type & (ACTION_SINGLE | ACTION_MULTIPLE)
	    && child_info->msginfo_list) {


		SummaryView *summaryview  = NULL;
		GSList      *cur;
		MsgInfo     *msginfo, *nmi;
		char        *file;
		gboolean     modified_something = FALSE;
		FolderItem  *last_item = NULL;
		if (mainwindow_get_mainwindow ())
			summaryview = mainwindow_get_mainwindow ()->summaryview;
		for (cur = child_info->msginfo_list; cur; cur = cur->next) {
			msginfo = (MsgInfo *)cur->data;
			if (!(msginfo &&
			    msginfo->folder && msginfo->folder->cache))
				continue;
			file = procmsg_get_message_file_path (msginfo);
			if (!file)
				continue;
			nmi = procheader_parse_file (file, msginfo->flags, TRUE, FALSE);
			if (!nmi)
				continue;
			if (msginfo->mtime != nmi->mtime || msginfo->size != nmi->size) {
				nmi->folder = msginfo->folder;
				nmi->msgnum = msginfo->msgnum;
				msgcache_update_msg (msginfo->folder->cache, nmi);
				modified_something = TRUE;
				last_item = nmi->folder;
			}
			procmsg_msginfo_free (nmi);
			if (summaryview && summaryview->displayed &&
		    	    summaryview->folder_item == msginfo->folder &&
			    summary_get_msgnum(summaryview, summaryview->displayed) == msginfo->msgnum)
				summary_redisplay_msg(summaryview);

		}
		if (modified_something && last_item &&
		    summaryview && summaryview->folder_item == last_item) {
			summary_show (summaryview, summaryview->folder_item);
		}
		g_slist_free (child_info->msginfo_list);
		child_info->msginfo_list = NULL;
	}

	if (!child_info->pid)
		child_info->children->nb--;

	wait_for_children(child_info->children);
}
