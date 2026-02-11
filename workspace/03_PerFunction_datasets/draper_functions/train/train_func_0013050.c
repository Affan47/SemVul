_gth_browser_add_file_menu_item (GthBrowser *browser,
				 GtkWidget  *menu,
			 	 GFile      *file,
			 	 const char *display_name,
			 	 GthAction   action,
				 int         steps)
{
	GthFileSource *file_source;
	GFileInfo     *info;

	file_source = gth_main_get_file_source (file);
	info = gth_file_source_get_file_info (file_source, file, GFILE_DISPLAY_ATTRIBUTES);
	if (info != NULL) {
		_gth_browser_add_file_menu_item_full (browser,
						      menu,
						      file,
						      g_file_info_get_icon (info),
						      (display_name != NULL) ? display_name : g_file_info_get_display_name (info),
						      action,
						      steps,
						      -1);
		g_object_unref (info);
	}
	else {
		GIcon *icon;
		char  *name;

		icon = _g_file_get_icon (file);
		name = _g_file_get_display_name (file);
		_gth_browser_add_file_menu_item_full (browser,
						      menu,
						      file,
						      icon,
						      (display_name != NULL) ? display_name : name,
						      action,
						      steps,
						      -1);

		g_free (name);
		g_object_unref (icon);
	}

	g_object_unref (file_source);
}
