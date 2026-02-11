notify_opendialog_clicked (GtkWidget * igad)
{
	GtkTreeView *view;
	GtkTreeIter iter;
	struct notify_per_server *servnot;

	view = g_object_get_data (G_OBJECT (notify_window), "view");
	if (gtkutil_treeview_get_selected (view, &iter, NPS_COLUMN, &servnot, -1))
	{
		if (servnot)
			open_query (servnot->server, servnot->notify->name, TRUE);
	}
}
