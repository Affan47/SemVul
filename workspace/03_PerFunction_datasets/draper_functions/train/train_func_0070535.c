pk_catalog_process_type_part (PkCatalogState *state, PkCatalogMode mode, const gchar *distro_id_part)
{
	gchar *data = NULL;
	gchar **list = NULL;
	gchar *key = NULL;
	guint i;
	const gchar *type;
	GPtrArray *array = NULL;


	type = pk_catalog_mode_to_string (mode);
	if (distro_id_part == NULL)
		key = g_strdup (type);
	else
		key = g_strdup_printf ("%s(%s)", type, distro_id_part);
	data = g_key_file_get_string (state->file, PK_CATALOG_FILE_HEADER, key, NULL);


	if (data == NULL)
		goto out;


	if (mode == PK_CATALOG_MODE_PACKAGES)
		array = state->array_packages;
	if (mode == PK_CATALOG_MODE_FILES)
		array = state->array_files;
	if (mode == PK_CATALOG_MODE_PROVIDES)
		array = state->array_provides;


	list = g_strsplit_set (data, ";, ", 0);
	for (i=0; list[i] != NULL; i++)
		if (list[i][0] != '\0')
			g_ptr_array_add (array, g_strdup (list[i]));
out:
	g_strfreev (list);
	g_free (key);
	g_free (data);
}
