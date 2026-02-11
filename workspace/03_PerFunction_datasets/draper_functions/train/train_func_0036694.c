pk_package_sack_get_update_detail_cb (GObject *source_object, GAsyncResult *res, PkPackageSackState *state)
{
	PkClient *client = PK_CLIENT (source_object);
	GError *error = NULL;
	PkResults *results;
	GPtrArray *update_details = NULL;
	PkUpdateDetail *item;
	guint i;
	PkPackage *package;
	gchar *package_id;
	gchar *updates;
	gchar *obsoletes;
	gchar **vendor_urls;
	gchar **bugzilla_urls;
	gchar **cve_urls;
	PkRestartEnum restart;
	gchar *update_text;
	gchar *changelog;
	PkUpdateStateEnum state_enum;
	gchar *issued;
	gchar *updated;


	results = pk_client_generic_finish (client, res, &error);
	if (results == NULL) {
		g_warning ("failed to update_detail: %s", error->message);
		pk_package_sack_merge_bool_state_finish (state, error);
		g_error_free (error);
		goto out;
	}


	update_details = pk_results_get_update_detail_array (results);
	if (update_details->len == 0) {
		error = g_error_new (1, 0, "no update details found!");
		pk_package_sack_merge_bool_state_finish (state, error);
		g_error_free (error);
		goto out;
	}


	for (i = 0; i < update_details->len; i++) {
		item = g_ptr_array_index (update_details, i);
		g_object_get (item,
			      "package-id", &package_id,
			      "updates", &updates,
			      "obsoletes", &obsoletes,
			      "vendor-urls", &vendor_urls,
			      "bugzilla-urls", &bugzilla_urls,
			      "cve-urls", &cve_urls,
			      "restart", &restart,
			      "update-text", &update_text,
			      "changelog", &changelog,
			      "state", &state_enum,
			      "issued", &issued,
			      "updated", &updated,
			      NULL);


		package = pk_package_sack_find_by_id (state->sack, package_id);
		if (package == NULL) {
			g_warning ("failed to find %s", package_id);
			goto skip;
		}


		g_object_set (package,
			      "update-updates", updates,
			      "update-obsoletes", obsoletes,
			      "update-vendor-urls", vendor_urls,
			      "update-bugzilla-urls", bugzilla_urls,
			      "update-cve-urls", cve_urls,
			      "update-restart", restart,
			      "update-text", update_text,
			      "update-changelog", changelog,
			      "update-state", state_enum,
			      "update-issued", issued,
			      "update-updated", updated,
			      NULL);
		g_object_unref (package);
skip:
		g_free (package_id);
		g_free (updates);
		g_free (obsoletes);
		g_strfreev (vendor_urls);
		g_strfreev (bugzilla_urls);
		g_strfreev (cve_urls);
		g_free (update_text);
		g_free (changelog);
		g_free (issued);
		g_free (updated);
	}


	state->ret = TRUE;


	pk_package_sack_merge_bool_state_finish (state, error);
out:
	if (results != NULL)
		g_object_unref (results);
	if (update_details != NULL)
		g_ptr_array_unref (update_details);
}
