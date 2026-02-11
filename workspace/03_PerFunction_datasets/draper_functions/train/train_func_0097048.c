panel_place_menu_item_finalize (GObject *object)
{
	PanelPlaceMenuItem *menuitem = (PanelPlaceMenuItem *) object;

	gconf_client_remove_dir (panel_gconf_get_client (),
				 DESKTOP_IS_HOME_DIR_DIR,
				 NULL);
	gconf_client_remove_dir (panel_gconf_get_client (),
				 NAMES_DIR,
				 NULL);

	if (menuitem->priv->bookmarks_monitor != NULL) {
		g_file_monitor_cancel (menuitem->priv->bookmarks_monitor);
		g_object_unref (menuitem->priv->bookmarks_monitor);
	}
	menuitem->priv->bookmarks_monitor = NULL;

	if (menuitem->priv->drive_changed_id)
		g_signal_handler_disconnect (menuitem->priv->volume_monitor,
					     menuitem->priv->drive_changed_id);
	menuitem->priv->drive_changed_id = 0;

	if (menuitem->priv->drive_connected_id)
		g_signal_handler_disconnect (menuitem->priv->volume_monitor,
					     menuitem->priv->drive_connected_id);
	menuitem->priv->drive_connected_id = 0;

	if (menuitem->priv->drive_disconnected_id)
		g_signal_handler_disconnect (menuitem->priv->volume_monitor,
					     menuitem->priv->drive_disconnected_id);
	menuitem->priv->drive_disconnected_id = 0;

	if (menuitem->priv->volume_added_id)
		g_signal_handler_disconnect (menuitem->priv->volume_monitor,
					     menuitem->priv->volume_added_id);
	menuitem->priv->volume_added_id = 0;

	if (menuitem->priv->volume_changed_id)
		g_signal_handler_disconnect (menuitem->priv->volume_monitor,
					     menuitem->priv->volume_changed_id);
	menuitem->priv->volume_changed_id = 0;

	if (menuitem->priv->volume_removed_id)
		g_signal_handler_disconnect (menuitem->priv->volume_monitor,
					     menuitem->priv->volume_removed_id);
	menuitem->priv->volume_removed_id = 0;

	if (menuitem->priv->mount_added_id)
		g_signal_handler_disconnect (menuitem->priv->volume_monitor,
					     menuitem->priv->mount_added_id);
	menuitem->priv->mount_added_id = 0;

	if (menuitem->priv->mount_changed_id)
		g_signal_handler_disconnect (menuitem->priv->volume_monitor,
					     menuitem->priv->mount_changed_id);
	menuitem->priv->mount_changed_id = 0;

	if (menuitem->priv->mount_removed_id)
		g_signal_handler_disconnect (menuitem->priv->volume_monitor,
					     menuitem->priv->mount_removed_id);
	menuitem->priv->mount_removed_id = 0;

	if (menuitem->priv->volume_monitor != NULL)
		g_object_unref (menuitem->priv->volume_monitor);
	menuitem->priv->volume_monitor = NULL;

	G_OBJECT_CLASS (panel_place_menu_item_parent_class)->finalize (object);
}
