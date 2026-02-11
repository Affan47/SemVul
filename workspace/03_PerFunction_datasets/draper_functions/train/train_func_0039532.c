files_has_file (NautilusPropertiesWindow *window)
{
	GList *l;

	for (l = window->details->target_files; l != NULL; l = l->next) {
		NautilusFile *file;
		file = NAUTILUS_FILE (l->data);
		if (!nautilus_file_is_directory (file)) {
			return TRUE;
		}
	}

	return FALSE;
}
