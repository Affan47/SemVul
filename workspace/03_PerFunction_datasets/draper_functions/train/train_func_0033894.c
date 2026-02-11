files_list_free(struct list_head *files)
{
	struct filename *filename;
	struct filename *temp;

	list_for_each_entry_safe(filename, temp, files, entry) {
		dbg("cleaning up filename %s\n", filename->filename);
		free(filename->filename);
		if (filename->basename)
			free(filename->basename);
		if (filename->id)
			free(filename->id);
		if (filename->key)
			free(filename->key);
		if (filename->caption)
			free(filename->caption);
		if (filename->original_url)
			free(filename->original_url);
		free(filename);
	}
}
