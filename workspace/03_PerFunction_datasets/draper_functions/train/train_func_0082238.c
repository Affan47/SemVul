update_directory_in_scripts_menu (NautilusView *view, NautilusDirectory *directory)
{
	char *menu_path, *popup_path, *popup_bg_path;
	GList *file_list, *filtered, *node;
	gboolean any_scripts;
	NautilusFile *file;
	NautilusDirectory *dir;
	char *uri;
	char *escaped_path;

	uri = nautilus_directory_get_uri (directory);
	escaped_path = escape_action_path (uri + scripts_directory_uri_length);
	g_free (uri);
	menu_path = g_strconcat (NAUTILUS_VIEW_MENU_PATH_SCRIPTS_PLACEHOLDER,
				 escaped_path,
				 NULL);
	popup_path = g_strconcat (NAUTILUS_VIEW_POPUP_PATH_SCRIPTS_PLACEHOLDER,
				  escaped_path,
				  NULL);
	popup_bg_path = g_strconcat (NAUTILUS_VIEW_POPUP_PATH_BACKGROUND_SCRIPTS_PLACEHOLDER,
				     escaped_path,
				     NULL);
	g_free (escaped_path);

	file_list = nautilus_directory_get_file_list (directory);
	filtered = nautilus_file_list_filter_hidden (file_list, FALSE);
	nautilus_file_list_free (file_list);

	file_list = nautilus_file_list_sort_by_display_name (filtered);

	any_scripts = FALSE;
	for (node = file_list; node != NULL; node = node->next) {
		file = node->data;

		if (nautilus_file_is_launchable (file)) {
			add_script_to_scripts_menus (view, file, menu_path, popup_path, popup_bg_path);
			any_scripts = TRUE;
		} else if (nautilus_file_is_directory (file)) {
			uri = nautilus_file_get_uri (file);
			if (directory_belongs_in_scripts_menu (uri)) {
				dir = nautilus_directory_get_by_uri (uri);
				add_directory_to_scripts_directory_list (view, dir);
				nautilus_directory_unref (dir);

				add_submenu_to_directory_menus (view,
								view->details->scripts_action_group,
								view->details->scripts_merge_id,
								file, menu_path, popup_path, popup_bg_path);

				any_scripts = TRUE;
			}
			g_free (uri);
		}
	}

	nautilus_file_list_free (file_list);

	g_free (popup_path);
	g_free (popup_bg_path);
	g_free (menu_path);

	return any_scripts;
}
