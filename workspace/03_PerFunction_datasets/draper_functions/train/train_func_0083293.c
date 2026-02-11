folderview_update_search_icon(FolderItem *item, gboolean matches)
{
	GList *list;
	FolderView *folderview;
	GtkCMCTree *ctree;
	GtkCMCTreeNode *node;

	cm_return_if_fail(item != NULL);

	for (list = folderview_list; list != NULL; list = list->next) {
		folderview = (FolderView *)list->data;
		ctree = GTK_CMCTREE(folderview->ctree);

		node = gtk_cmctree_find_by_row_data(ctree, NULL, item);
		if (node && item->search_match != matches) {
			item->search_match = matches;
			folderview_update_node(folderview, node);
		}
	}
}
