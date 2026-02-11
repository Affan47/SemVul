summary_execute_delete(SummaryView *summaryview)
{
	GtkCMCTree *ctree = GTK_CMCTREE(summaryview->ctree);
	GSList *cur;


	if (!summaryview->folder_item->folder->account || summaryview->folder_item->folder->account->imap_use_trash) {
		gtk_cmctree_pre_recursive
			(ctree, NULL, summary_execute_delete_func, summaryview);
	}
	if (!summaryview->mlist) return;

	hooks_unregister_hook(MSGINFO_UPDATE_HOOKLIST,
		summaryview->msginfo_update_callback_id);

	folder_item_remove_msgs(summaryview->folder_item,
				summaryview->mlist);

	summaryview->msginfo_update_callback_id =
		hooks_register_hook(MSGINFO_UPDATE_HOOKLIST,
			summary_update_msg, (gpointer) summaryview);
	if (!summaryview->folder_item->folder->account || summaryview->folder_item->folder->account->imap_use_trash) {
		for (cur = summaryview->mlist; cur != NULL && cur->data != NULL; cur = cur->next)
			procmsg_msginfo_free((MsgInfo *)cur->data);
	}
	g_slist_free(summaryview->mlist);
	summaryview->mlist = NULL;
}
