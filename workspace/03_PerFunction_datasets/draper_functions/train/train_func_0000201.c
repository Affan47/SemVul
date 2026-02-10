child_watch(GPid pid, gint status, gpointer data) {
	GtkTextBuffer *buffer;
	GtkTextIter iter;
	gchar *tmpc, *str, buf[5];

	sprintf(buf, "%i", WEXITSTATUS(status));
	str = g_strconcat(_("Rsync process exit status: "), buf, "\n", NULL);

	buffer = gtk_text_view_get_buffer((GtkTextView*)data);
	if (status == 0) {
		gtk_text_buffer_insert_at_cursor(buffer, str, -1);
	} else {
		gtk_text_buffer_get_end_iter(buffer, &iter);
		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, str, -1, "fore-red", NULL);
		tmpc = g_strconcat(error_list, str, NULL);
		g_free(error_list);
		error_list = tmpc;
		had_error = TRUE;
	}
	scroll_to_end((GtkTextView*)data, FALSE);

	if (config_log) fputs(str, log_file);
	g_free(str);
	rsync_cleanup(NULL);
	must_scroll = TRUE;
}
