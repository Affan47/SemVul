iter_is_bookmark(GigoloWindow *window, GtkTreeModel *model, GtkTreeIter *iter)
{
	gint ref_type;
	gpointer ref;

	gtk_tree_model_get(model, iter, GIGOLO_WINDOW_COL_REF_TYPE, &ref_type,
									GIGOLO_WINDOW_COL_REF, &ref, -1);

	if (ref_type == GIGOLO_WINDOW_REF_TYPE_MOUNT && gigolo_backend_gvfs_is_mount(ref))
	{
		gchar *uri;
		gboolean found = FALSE;
		GigoloWindowPrivate *priv = GIGOLO_WINDOW_GET_PRIVATE(window);

		gigolo_backend_gvfs_get_name_and_uri_from_mount(ref, NULL, &uri);

		found = (gigolo_settings_get_bookmark_by_uri(priv->settings, uri) != NULL);

		g_free(uri);
		return found;
	}

	return TRUE;
}
