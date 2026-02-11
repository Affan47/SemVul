get_file_pixbuf (GSearchWindow * gsearch,
                 GFileInfo * file_info)
{
	GdkPixbuf * pixbuf;
	GIcon * icon = NULL;
	const gchar * thumbnail_path = NULL;

	if (file_info == NULL) {
		return NULL;
	}

	icon = g_file_info_get_icon (file_info);

	if (gsearch->show_thumbnails == TRUE) {
		thumbnail_path = g_file_info_get_attribute_byte_string (file_info, G_FILE_ATTRIBUTE_THUMBNAIL_PATH);
	}

	if (thumbnail_path != NULL) {
		pixbuf = gsearchtool_get_thumbnail_image (thumbnail_path);
	}
	else {
		gchar * icon_string;

		icon_string = g_icon_to_string (icon);
		pixbuf = (GdkPixbuf *) g_hash_table_lookup (gsearch->search_results_filename_hash_table, icon_string);

		if (pixbuf == NULL) {
			pixbuf = get_themed_icon_pixbuf (G_THEMED_ICON (icon), ICON_SIZE, gtk_icon_theme_get_default ());
			g_hash_table_insert (gsearch->search_results_filename_hash_table, g_strdup (icon_string), pixbuf);
		}
		g_free (icon_string);
	}
	return pixbuf;
}
