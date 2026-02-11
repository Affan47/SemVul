treebrowser_track_current(void)
{

	GeanyDocument	*doc 		= document_get_current();
	gchar 			*path_current;
	gchar			**path_segments = NULL;
	gchar 			*froot = NULL;

	if (doc != NULL && doc->file_name != NULL && g_path_is_absolute(doc->file_name))
	{
		path_current = utils_get_locale_from_utf8(doc->file_name);


		if (! treebrowser_search(path_current, NULL))
		{


			froot = path_is_in_dir(addressbar_last_address, g_path_get_dirname(path_current));

			if (froot == NULL)
				froot = g_strdup(G_DIR_SEPARATOR_S);

			if (utils_str_equal(froot, addressbar_last_address) != TRUE)
				treebrowser_chroot(froot);

			treebrowser_expand_to_path(froot, path_current);
		}

		g_strfreev(path_segments);
		g_free(froot);
		g_free(path_current);

		return FALSE;
	}
	return FALSE;
}
