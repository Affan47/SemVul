file_dialog_sync_history(FileDialog *fdlg, gboolean dir_only)
{
	if (!fdlg->dest_path) return;

	if (!dir_only ||
	    (dir_only && isdir(fdlg->dest_path)) )
		{
		tab_completion_append_to_history(fdlg->entry, fdlg->dest_path);
		}
	else
		{
		gchar *buf = remove_level_from_path(fdlg->dest_path);
		tab_completion_append_to_history(fdlg->entry, buf);
		g_free(buf);
		}
}
