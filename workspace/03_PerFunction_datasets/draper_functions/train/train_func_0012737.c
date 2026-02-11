summary_move_row_to(SummaryView *summaryview, GtkCMCTreeNode *row,
				FolderItem *to_folder)
{
	GtkCMCTree *ctree = GTK_CMCTREE(summaryview->ctree);
	MsgInfo *msginfo;

	cm_return_if_fail(to_folder != NULL);

	msginfo = gtk_cmctree_node_get_row_data(ctree, row);
	cm_return_if_fail(msginfo);
	if (MSG_IS_LOCKED(msginfo->flags))
		return;

	procmsg_msginfo_set_to_folder(msginfo, to_folder);
	if (MSG_IS_DELETED(msginfo->flags))
		summaryview->deleted--;
	if (MSG_IS_COPY(msginfo->flags)) {
		summaryview->copied--;
	}
	if (!MSG_IS_MOVE(msginfo->flags)) {
		summary_msginfo_change_flags(msginfo, 0, MSG_MOVE, MSG_DELETED,
			MSG_COPY | MSG_MOVE_DONE);
		summaryview->moved++;
	} else {
		summary_msginfo_unset_flags(msginfo, MSG_DELETED, MSG_COPY);
	}

	if (!prefs_common.immediate_exec) {
		summary_set_row_marks(summaryview, row);
	} else if (msginfo->folder->folder->account && !msginfo->folder->folder->account->imap_use_trash) {
		summary_set_row_marks(summaryview, row);
	}

	debug_print("Message %d is set to move to %s\n",
		    msginfo->msgnum, to_folder->path);
}
