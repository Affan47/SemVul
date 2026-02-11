setAutoResize(bool vl)
{
	int i;

	for (i = 0; i < columnCount(); i++)
		gtk_tree_view_column_set_sizing(gt_tree_view_find_column(GTK_TREE_VIEW(widget), i), vl ? GTK_TREE_VIEW_COLUMN_AUTOSIZE : GTK_TREE_VIEW_COLUMN_FIXED);

	_auto_resize = vl;
}
