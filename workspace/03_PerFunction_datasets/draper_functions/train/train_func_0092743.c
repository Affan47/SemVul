share_settings_dialog_run (const gchar *path, gboolean standalone)
{
	GtkTreeIter   iter;


	if (table_get_iter_with_path (path, &iter))
		share_settings_dialog_run_for_iter (path, &iter, standalone);
	else
		share_settings_dialog_run_for_iter (path, NULL, standalone);
}
