get_icon (GFile *file)
{
	const gchar** icon_names;
	GtkIconInfo* icon_info;
	GIcon* icon;
	GdkPixbuf* pixbuf = NULL;
	GFileInfo* file_info;
	GError *error = NULL;

	file_info = g_file_query_info (file,
				       G_FILE_ATTRIBUTE_STANDARD_ICON,
				       G_FILE_QUERY_INFO_NONE,
				       NULL,
				       &error);

	if (file_info != NULL)
	{
		icon = g_file_info_get_icon(file_info);
		g_object_get (icon, "names", &icon_names, NULL);
		icon_info = gtk_icon_theme_choose_icon (gtk_icon_theme_get_default(),
							icon_names,
							ICON_SIZE,
							GTK_ICON_LOOKUP_GENERIC_FALLBACK);
		if (icon_info != NULL)
		{
			pixbuf = gtk_icon_info_load_icon (icon_info, NULL);
			gtk_icon_info_free(icon_info);
		}
		g_object_unref (file_info);
	}

	if (pixbuf == NULL)
	{
		pixbuf = gtk_icon_theme_load_icon (gtk_icon_theme_get_default(),
						   GTK_STOCK_MISSING_IMAGE,
						   ICON_SIZE,
						   GTK_ICON_LOOKUP_GENERIC_FALLBACK,
						   NULL);
	}

	return pixbuf;
}
