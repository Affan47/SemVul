connection_added (NMRemoteSettings *settings,
                  NMRemoteConnection *connection,
                  gpointer user_data)
{
	NMConnectionList *self = NM_CONNECTION_LIST (user_data);
	GtkTreeIter parent_iter, iter;
	NMSettingConnection *s_con;
	char *last_used;
	gboolean expand = TRUE;

	if (!get_parent_iter_for_connection (self, connection, &parent_iter))
		return;

	s_con = nm_connection_get_setting_connection (NM_CONNECTION (connection));

	last_used = format_last_used (nm_setting_connection_get_timestamp (s_con));

	gtk_tree_store_append (GTK_TREE_STORE (self->model), &iter, &parent_iter);
	gtk_tree_store_set (GTK_TREE_STORE (self->model), &iter,
	                    COL_ID, nm_setting_connection_get_id (s_con),
	                    COL_LAST_USED, last_used,
	                    COL_TIMESTAMP, nm_setting_connection_get_timestamp (s_con),
	                    COL_CONNECTION, connection,
	                    -1);

	g_free (last_used);

	if (self->displayed_type) {
		GType added_type;

		gtk_tree_model_get (self->model, &parent_iter,
		                    COL_GTYPE, &added_type,
		                    -1);
		if (added_type != self->displayed_type)
			expand = FALSE;
	}

	if (expand) {
		GtkTreePath *path, *filtered_path;

		path = gtk_tree_model_get_path (self->model, &parent_iter);
		filtered_path = gtk_tree_model_filter_convert_child_path_to_path (self->filter, path);
		gtk_tree_view_expand_row (self->connection_list, filtered_path, FALSE);
		gtk_tree_path_free (filtered_path);
		gtk_tree_path_free (path);
	}

	g_signal_connect (connection, NM_REMOTE_CONNECTION_REMOVED, G_CALLBACK (connection_removed), self);
	g_signal_connect (connection, NM_REMOTE_CONNECTION_UPDATED, G_CALLBACK (connection_updated), self);
	gtk_tree_model_filter_refilter (self->filter);
}
