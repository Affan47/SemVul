locations_from_file_list (GList *file_list)
{
	NautilusFile *file;
	GList *l, *ret;

	ret = NULL;

	for (l = file_list; l != NULL; l = l->next) {
		file = NAUTILUS_FILE (l->data);
		ret = g_list_prepend (ret, nautilus_file_get_location (file));
	}

	return g_list_reverse (ret);
}
