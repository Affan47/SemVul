gpk_application_get_repo_list_cb (PkClient *client, GAsyncResult *res, GpkApplicationPrivate *priv)
{
	PkResults *results;
	GError *error = NULL;
	PkError *error_code = NULL;
	GPtrArray *array = NULL;
	PkRepoDetail *item;
	guint i;
	GtkWindow *window;
	gchar *repo_id = NULL;
	gchar *description = NULL;


	results = pk_client_generic_finish (client, res, &error);
	if (results == NULL) {
		g_warning ("failed to get list of repos: %s", error->message);
		g_error_free (error);
		goto out;
	}


	error_code = pk_results_get_error_code (results);
	if (error_code != NULL) {
		g_warning ("failed to repo list: %s, %s", pk_error_enum_to_string (pk_error_get_code (error_code)), pk_error_get_details (error_code));


		if (pk_error_get_code (error_code) != PK_ERROR_ENUM_TRANSACTION_CANCELLED) {
			window = GTK_WINDOW (gtk_builder_get_object (priv->builder, "window_manager"));
			gpk_error_dialog_modal (window, gpk_error_enum_to_localised_text (pk_error_get_code (error_code)),
						gpk_error_enum_to_localised_message (pk_error_get_code (error_code)), pk_error_get_details (error_code));
		}
		goto out;
	}


	array = pk_results_get_repo_detail_array (results);
	for (i=0; i<array->len; i++) {
		item = g_ptr_array_index (array, i);
		g_object_get (item,
			      "repo-id", &repo_id,
			      "description", &description,
			      NULL);

		g_debug ("repo = %s:%s", repo_id, description);

		if (description != NULL)
			g_hash_table_insert (priv->repos, g_strdup (repo_id), g_strdup (description));
		g_free (repo_id);
		g_free (description);
	}

out:
	if (error_code != NULL)
		g_object_unref (error_code);
	if (array != NULL)
		g_ptr_array_unref (array);
	if (results != NULL)
		g_object_unref (results);
}
