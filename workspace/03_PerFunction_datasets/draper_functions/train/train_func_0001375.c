brasero_data_project_load_contents (BraseroDataProject *self,
				    GSList *grafts,
				    GSList *excluded)
{
	GSList *iter;
	GSList *folders = NULL;
	BraseroDataProjectPrivate *priv;

	priv = BRASERO_DATA_PROJECT_PRIVATE (self);
	priv->is_loading_contents = 1;

	for (iter = grafts; iter; iter = iter->next) {
		BraseroGraftPt *graft;
		GFile *file;
		gchar *path;
		gchar *uri;

		graft = iter->data;

		if (graft->uri) {
			file = g_file_new_for_uri (graft->uri);
			uri = g_file_get_uri (file);
			g_object_unref (file);
		}
		else
			uri = NULL;

		if (graft->path) {

			if (g_str_has_suffix (graft->path, G_DIR_SEPARATOR_S)) {
				int len;

				len = strlen (graft->path);
				path = g_strndup (graft->path, len - 1);
			}
			else
				path = g_strdup (graft->path);
		}
		else
			path = NULL;

		folders = brasero_data_project_add_path (self,
							 path,
							 uri,
							 folders);
		g_free (path);
		g_free (uri);
	}

	for (iter = excluded; iter; iter = iter->next) {
		gchar *uri;
		GFile *file;

		file = g_file_new_for_uri (iter->data);
		uri = g_file_get_uri (file);
		g_object_unref (file);

		folders = brasero_data_project_add_excluded_uri (self,
								 uri,
								 folders);
		g_free (uri);
	}


	for (iter = folders; iter; iter = iter->next) {
		BraseroURINode *graft;
		BraseroFileNode *tmp;
		gchar *uri;

		tmp = iter->data;


		uri = brasero_data_project_node_to_uri (self, tmp);
		if (!uri) {


			tmp->is_fake = TRUE;
			tmp->is_loading = FALSE;
			tmp->is_reloading = FALSE;

			graft = brasero_data_project_uri_ensure_graft (self, NEW_FOLDER);
			brasero_file_node_graft (tmp, graft);


			continue;
		}


		graft = brasero_data_project_uri_ensure_graft (self, uri);
		brasero_file_node_graft (tmp, graft);
		g_free (uri);


	}
	g_slist_free (folders);

	priv->loading = brasero_data_project_load_contents_notify (self);

	priv->is_loading_contents = 0;
	return priv->loading;
}
