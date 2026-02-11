summary_select_by_msg_list(SummaryView	*summaryview, GSList *msginfos)
{
	GtkCMCTree *ctree;
	GSList *msgnum_list, *walk;
	gboolean froze = FALSE;

	ctree = GTK_CMCTREE(summaryview->ctree);

	msgnum_list = procmsg_get_number_list_for_msgs(msginfos);

	START_LONG_OPERATION(summaryview, FALSE);
	for(walk = msgnum_list; walk; walk = walk->next) {
		GtkCMCTreeNode *node;
		node = summary_find_msg_by_msgnum(summaryview, GPOINTER_TO_UINT(walk->data));
		gtk_cmctree_select(ctree, node);
	}
	END_LONG_OPERATION(summaryview);
	g_slist_free(msgnum_list);
}
