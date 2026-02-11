compose_attach_from_list(Compose *compose, GList *file_list, gboolean free_data)
{
	if (compose && file_list) {
		GList *tmp;

		for ( tmp = file_list; tmp; tmp = tmp->next) {
			gchar *file = (gchar *) tmp->data;
			gchar *utf8_filename = conv_filename_to_utf8(file);
			compose_attach_append(compose, file, utf8_filename, NULL, NULL);
			compose_changed_cb(NULL, compose);
			if (free_data) {
			g_free(file);
				tmp->data = NULL;
			}
			g_free(utf8_filename);
		}
	}
}
