recent_get_recent_files(void)
{
	static GeanyRecentFiles grf = { RECENT_FILE_FILE, NULL, NULL, NULL, NULL };

	if (G_UNLIKELY(grf.recent_queue == NULL))
	{
		grf.recent_queue = ui_prefs.recent_queue;
		grf.menubar = ui_widgets.recent_files_menu_menubar;
		grf.toolbar = geany_menu_button_action_get_menu(GEANY_MENU_BUTTON_ACTION(
						toolbar_get_action_by_name("Open")));
		grf.activate_cb = recent_file_activate_cb;
	}
	return &grf;
}
