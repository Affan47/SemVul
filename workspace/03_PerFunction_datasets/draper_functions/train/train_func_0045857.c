sidebar_update_restore_selection (NemoPlacesSidebar *sidebar,
				  const gchar *location,
				  const gchar *last_uri)
{
	RestoreLocationData data;
	GtkTreeSelection *selection;

	data.location = location;
	data.last_uri = last_uri;
	data.sidebar = sidebar;
	data.path = NULL;

	gtk_tree_model_foreach (GTK_TREE_MODEL (sidebar->store),
				restore_selection_foreach, &data);

	if (data.path != NULL) {
		selection = gtk_tree_view_get_selection (sidebar->tree_view);
		gtk_tree_selection_select_path (selection, data.path);
		gtk_tree_path_free (data.path);
	}
}
