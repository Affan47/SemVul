sort_criterion_changes_due_to_user (GtkTreeView *tree_view)
{
	GList *columns, *p;
	GtkTreeViewColumn *column;
	GSignalInvocationHint *ihint;
	gboolean ret;

	ret = FALSE;

	columns = gtk_tree_view_get_columns (tree_view);
	for (p = columns; p != NULL; p = p->next) {
		column = p->data;
		ihint = g_signal_get_invocation_hint (column);
		if (ihint != NULL) {
			ret = TRUE;
			break;
		}
	}
	g_list_free (columns);

	return ret;
}
