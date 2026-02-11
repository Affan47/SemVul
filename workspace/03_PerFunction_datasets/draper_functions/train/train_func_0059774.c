gfire_menu_action_reload_lconfig_cb(PurplePluginAction *p_action)
{
	if(!gfire_game_load_config_xml(TRUE))
		purple_notify_message(p_action->context, PURPLE_NOTIFY_MSG_ERROR, _("Gfire XML Reload"), _("Reloading gfire_game_config.xml"), _("Operation failed. File not found or content was incorrect."), NULL, NULL);
	else
		purple_notify_message(p_action->context, PURPLE_NOTIFY_MSG_INFO, _("Gfire XML Reload"), _("Reloading gfire_game_config.xml"), _("Reloading was successful."), NULL, NULL);
}
