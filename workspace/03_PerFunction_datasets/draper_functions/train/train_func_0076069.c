send_progress_dialog_destroy(SendProgressDialog *dialog)
{
	cm_return_if_fail(dialog != NULL);
	if (!prefs_common.send_dialog_invisible) {
		progress_dialog_destroy(dialog->dialog);
	}
	g_free(dialog);
	send_dialog = NULL;
}
