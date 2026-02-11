canonicalize_file_replace(const gchar *file)
{
	gchar *tmp_file;

	tmp_file = get_tmp_file();

	if (canonicalize_file(file, tmp_file) < 0) {
		g_free(tmp_file);
		return -1;
	}

	if (move_file(tmp_file, file, TRUE) < 0) {
		g_warning("can't replace %s .\n", file);
		claws_unlink(tmp_file);
		g_free(tmp_file);
		return -1;
	}

	g_free(tmp_file);
	return 0;
}
