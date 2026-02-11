panel_run_dialog_append_file (PanelRunDialog *dialog,
			      const char *file)
{
	char *utf8_file;

	if (!file)
		return;

	utf8_file = g_filename_to_utf8 (file, -1, NULL, NULL, NULL);

	if (utf8_file)
		panel_run_dialog_append_file_utf8 (dialog, utf8_file);

	g_free (utf8_file);
}
