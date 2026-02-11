brasero_pk_install_missing_app (BraseroPK *package,
                                const gchar *file_name,
                                int xid,
                                GCancellable *cancel)
{
	gchar *path;
	gboolean res;
	GPtrArray *missing_files;

	path = g_build_path (G_DIR_SEPARATOR_S,
	                     "/usr/bin/",
	                     file_name,
	                     NULL);

	if (g_slist_find_custom (already_tested, path, (GCompareFunc) g_strcmp0)) {
		g_free (path);
		return FALSE;
	}
	already_tested = g_slist_prepend (already_tested, g_strdup (path));

	missing_files = g_ptr_array_new ();
	g_ptr_array_add (missing_files, path);
	g_ptr_array_add (missing_files, NULL);

	res = brasero_pk_install_file_requirement (package, missing_files, xid, cancel);

	g_strfreev ((gchar **) missing_files->pdata);
	g_ptr_array_free (missing_files, FALSE);

	return res;
}
