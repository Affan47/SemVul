summary_search_unread_recursive(GtkCMCTree *ctree,
						GtkCMCTreeNode *node)
{
	MsgInfo *msginfo;

	if (node) {
		msginfo = gtk_cmctree_node_get_row_data(ctree, node);
		if (msginfo && MSG_IS_UNREAD(msginfo->flags) && !MSG_IS_IGNORE_THREAD(msginfo->flags))
			return TRUE;
		node = GTK_CMCTREE_ROW(node)->children;
	} else
		node = GTK_CMCTREE_NODE(GTK_CMCLIST(ctree)->row_list);

	while (node) {
		if (summary_search_unread_recursive(ctree, node) == TRUE)
			return TRUE;
		node = GTK_CMCTREE_ROW(node)->sibling;
	}

	return FALSE;
}
