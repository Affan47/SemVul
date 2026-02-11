pk_console_update_system (PkBitfield filters, GError **error)
{
	gboolean ret = TRUE;
	gchar **package_ids = NULL;
	PkPackageSack *sack = NULL;
	PkResults *results;


	pk_bitfield_add (filters, PK_FILTER_ENUM_NEWEST);
	results = pk_task_get_updates_sync (PK_TASK (task),
					    filters,
					    cancellable,
					    (PkProgressCallback) pk_console_progress_cb, NULL,
					    error);
	if (results == NULL) {
		ret = FALSE;
		goto out;
	}


	sack = pk_results_get_package_sack (results);
	package_ids = pk_package_sack_get_ids (sack);
	if (g_strv_length (package_ids) == 0) {
		pk_progress_bar_end (progressbar);

		g_print ("%s\n", _("No packages require updating to newer versions."));
		retval = PK_EXIT_CODE_NOTHING_USEFUL;
		ret = FALSE;
		goto out;
	}
	pk_task_update_packages_async (PK_TASK(task), package_ids, cancellable,
				       (PkProgressCallback) pk_console_progress_cb, NULL,
				       (GAsyncReadyCallback) pk_console_finished_cb, NULL);
out:
	if (sack != NULL)
		g_object_unref (sack);
	if (results != NULL)
		g_object_unref (results);
	g_strfreev (package_ids);
	return ret;
}
