summary_find_msg_by_msgnum(SummaryView *summaryview,
						guint msgnum)
{
	GtkCMCTree *ctree = GTK_CMCTREE(summaryview->ctree);
	GtkCMCTreeNode *node;
	MsgInfo *msginfo;

	node = GTK_CMCTREE_NODE(GTK_CMCLIST(ctree)->row_list);

	for (; node != NULL; node = gtkut_ctree_node_next(ctree, node)) {
		msginfo = gtk_cmctree_node_get_row_data(ctree, node);
		if (msginfo && msginfo->msgnum == msgnum) break;
	}

	return node;
}
