thread_iter_mark(GtkTreeIter *iter, GeanyDocument *doc)
{
	char *file;
	gint line;

	gtk_tree_model_get(model, iter, THREAD_FILE, &file, THREAD_LINE, &line, -1);

	if (line && !utils_filenamecmp(file, doc->real_path))
		sci_set_marker_at_line(doc->editor->sci, line - 1, MARKER_EXECUTE);
	g_free(file);
}
