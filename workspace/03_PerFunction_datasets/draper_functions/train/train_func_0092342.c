dbstore_move_file(const char *old_path, const char *new_path, const char *ext)
{
	char *old_file = h_strconcat(old_path, ext, (void *) 0);
	char *new_file = h_strconcat(new_path, ext, (void *) 0);

	if (file_exists(old_file)) {
		if (-1 == rename(old_file, new_file)) {
			g_warning("could not rename \"%s\" as \"%s\": %m",
				old_file, new_file);
		}
	}

	HFREE_NULL(old_file);
	HFREE_NULL(new_file);
}
