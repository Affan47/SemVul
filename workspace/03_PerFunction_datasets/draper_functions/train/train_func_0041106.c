panel_applet_save_position (AppletInfo *applet_info,
			    const char *id,
			    gboolean    immediate)
{
	const char  *toplevel_id;
	AppletData  *applet_data;

	g_return_if_fail (applet_info != NULL);
	g_return_if_fail (G_IS_OBJECT (applet_info->widget));

	if (!immediate) {
		if (!queued_position_source)
			queued_position_source =
				g_timeout_add_seconds (1,
						       (GSourceFunc) panel_applet_position_save_timeout,
						       NULL);

		if (!g_slist_find (queued_position_saves, applet_info))
			queued_position_saves =
				g_slist_prepend (queued_position_saves, applet_info);

		return;
	}

	if (!(toplevel_id = panel_applet_get_toplevel_id (applet_info)))
		return;

	applet_data = g_object_get_data (G_OBJECT (applet_info->widget),
					 PANEL_APPLET_DATA);

	g_settings_set_string (applet_info->settings,
			       PANEL_OBJECT_TOPLEVEL_ID_KEY,
			       toplevel_id);
	g_settings_set_enum (applet_info->settings,
			     PANEL_OBJECT_PACK_TYPE_KEY,
			     applet_data->pack_type);
	g_settings_set_int (applet_info->settings,
			    PANEL_OBJECT_PACK_INDEX_KEY,
			    applet_data->pack_index);
}
