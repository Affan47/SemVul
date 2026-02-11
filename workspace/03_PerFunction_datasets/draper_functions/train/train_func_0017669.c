menu_put_game ()
{
	gchar *prefix = "/Game/Select Game/";
	gchar path0[128], path[128];
	if (opt_game->group)
	{
		snprintf (path0, sizeof (path0), "%s%s/", prefix, opt_game->group);
	}
	else
	{
		snprintf (path0, sizeof (path0), "%s", prefix);
	}
	snprintf (path, sizeof (path), "%s%s", path0, opt_game->name);
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM
			(gtk_item_factory_get_widget (menu_factory, path)), TRUE);
}
