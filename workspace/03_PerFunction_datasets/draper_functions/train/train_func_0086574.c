nautilus_file_set_metadata_list (NautilusFile *file,
				 const char *key,
				 GList *list)
{
	char **val;
	int len, i;
	GList *l;

	g_return_if_fail (NAUTILUS_IS_FILE (file));
	g_return_if_fail (key != NULL);
	g_return_if_fail (key[0] != '\0');

	len = g_list_length (list);
	val = g_new (char *, len + 1);
	for (l = list, i = 0; l != NULL; l = l->next, i++) {
		val[i] = l->data;
	}
	val[i] = NULL;

	NAUTILUS_FILE_CLASS (G_OBJECT_GET_CLASS (file))->set_metadata_as_list (file, key, val);

	g_free (val);
}
