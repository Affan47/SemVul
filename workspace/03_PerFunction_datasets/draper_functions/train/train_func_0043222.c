drag_data_get_callback (GtkWidget *widget,
			GdkDragContext *context,
			GtkSelectionData *selection_data,
			guint info,
			guint time)
{
	GtkTreeView *tree_view;
	GtkTreeModel *model;
	GList *selection_cache;

	tree_view = GTK_TREE_VIEW (widget);

	model = gtk_tree_view_get_model (tree_view);

	if (model == NULL) {
		return;
	}

	selection_cache = g_object_get_data (G_OBJECT (context), "drag-info");
	if (selection_cache == NULL) {
		return;
	}

	nautilus_drag_drag_data_get_from_cache (selection_cache, context, selection_data, info, time);
}
