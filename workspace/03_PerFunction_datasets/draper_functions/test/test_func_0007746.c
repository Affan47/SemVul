thread_iter_unmark(GtkTreeIter *iter, gpointer gdata)
{
	char *file;
	gchar *state;
	gint line;
	gboolean stopped;

	gtk_tree_model_get(model, iter, THREAD_FILE, &file, THREAD_LINE, &line, THREAD_STATE,
		&state, -1);
	stopped = !strcmp(state, STOPPED);
	thread_prompt += gdata ? -stopped : !stopped;

	if (GPOINTER_TO_INT(gdata) != 2)
		utils_mark(file, line, FALSE, MARKER_EXECUTE);

	g_free(file);
	g_free(state);
}
