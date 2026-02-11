menu_put_player (gboolean first)
{
	gchar *path, *paths[4] = {
		"/Settings/Player/Human-Human", "/Settings/Player/Human-Machine",
		"/Settings/Player/Machine-Human", "/Settings/Player/Machine-Machine"};
	if (!state_gui_active) return;
	if (first) {ui_white = opt_white; ui_black = opt_black;}
	if (opt_infile)
	{
		gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM
		(gtk_item_factory_get_widget (menu_factory, "/Settings/Player/File")),
		              TRUE);

		return;
	}
	else if (ui_white == HUMAN && ui_black == HUMAN)
		path = paths[0];
	else if (ui_white == HUMAN && ui_black == MACHINE)
		path = paths[1];
	else if (ui_white == MACHINE && ui_black == HUMAN)
		path = paths[2];
	else if (ui_white == MACHINE && ui_black == MACHINE)
		path = paths[3];
	else
		return;
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM
			(gtk_item_factory_get_widget (menu_factory, path)), TRUE);
}
