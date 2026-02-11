workbook_new (void)
{
	static int count = 0;
	gboolean is_unique;
	Workbook  *wb;
	GOFileSaver *def_save = go_file_saver_get_default ();
	char const *extension = NULL;

	if (def_save != NULL)
		extension = go_file_saver_get_extension (def_save);
	if (extension == NULL)
		extension = "gnumeric";

	wb = g_object_new (WORKBOOK_TYPE, NULL);


	do {
		char *name, *nameutf8, *uri;

		count++;
		nameutf8 = g_strdup_printf (_("Book%d.%s"), count, extension);
		name = g_filename_from_utf8 (nameutf8, -1, NULL, NULL, NULL);
		if (!name) {
			name = g_strdup_printf ("Book%d.%s", count, extension);
		}
		uri = go_filename_to_uri (name);

		is_unique = go_doc_set_uri (GO_DOC (wb), uri);

		g_free (uri);
		g_free (name);
		g_free (nameutf8);
	} while (!is_unique);
	gnm_insert_meta_date (GO_DOC (wb), GSF_META_NAME_DATE_CREATED);
	return wb;
}
