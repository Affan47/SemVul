cm_store_entry_delete(struct cm_store_entry *entry)
{
	int ret;
	const char *filename;

	if (entry->cm_store_private != NULL) {
		filename = (const char *) entry->cm_store_private;
		ret = remove(filename);
		if (ret == 0) {
			cm_log(3, "Removed file \"%s\".\n", filename);
			talloc_free(entry->cm_store_private);
			entry->cm_store_private = NULL;
		} else {
			cm_log(0, "Failed to remove file \"%s\": %s.\n",
			       filename, strerror(errno));
		}
	} else {
		cm_log(3, "No file to remove for \"%s\".\n",
		       entry->cm_nickname);
		ret = 0;
	}
	return 0;
}
