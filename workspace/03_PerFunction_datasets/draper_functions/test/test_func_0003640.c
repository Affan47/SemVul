compose_attach_cb(GtkAction *action, gpointer data)
{
	Compose *compose = (Compose *)data;
	GList *file_list;

	if (compose->redirect_filename != NULL)
		return;


	manage_window_focus_in(compose->window, NULL, NULL);

	file_list = filesel_select_multiple_files_open(_("Select file"));

	if (file_list) {
		compose_attach_from_list(compose, file_list, TRUE);
		g_list_free(file_list);
	}
}
