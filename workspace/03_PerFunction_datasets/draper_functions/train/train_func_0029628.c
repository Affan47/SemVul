skype_actions(PurplePlugin *plugin, gpointer context)
{
	GList *m = NULL;
	PurpleMenuAction *act;

#ifndef SKYPENET
	act = purple_menu_action_new(_("Hide Skype"),
									PURPLE_CALLBACK(skype_silence),
									NULL, NULL);
	m = g_list_append(m, act);
	act = purple_menu_action_new(_("Check for Skype updates..."),
									PURPLE_CALLBACK(skype_program_update_check),
									NULL, NULL);
	m = g_list_append(m, act);
#endif
	if (this_plugin != NULL && this_plugin->path != NULL)
	{
		act = purple_menu_action_new(_("Check for plugin updates..."),
										PURPLE_CALLBACK(skype_plugin_update_check),
										NULL, NULL);
		m = g_list_append(m, act);
	}

	act = purple_menu_action_new(_("Search for buddies..."),
									PURPLE_CALLBACK(skype_show_search_users),
									NULL, NULL);
	m = g_list_append(m, act);

	act = purple_menu_action_new(_("Check Skype balance..."),
									PURPLE_CALLBACK(skype_display_skype_credit),
									NULL, NULL);
	m = g_list_append(m, act);
#ifndef SKYPENET
	act = purple_menu_action_new(_("Call..."),
									PURPLE_CALLBACK(skype_call_number_request),
									NULL, NULL);
	m = g_list_append(m, act);

#ifdef _WIN32
	act = purple_menu_action_new(_("Open Skype Options..."),
									PURPLE_CALLBACK(skype_open_skype_options),
									NULL, NULL);
	m = g_list_append(m, act);
#endif
#endif

	act = purple_menu_action_new(_("Verify mobile number..."),
									PURPLE_CALLBACK(skype_open_verify_mobile_number),
									NULL, NULL);
	m = g_list_append(m, act);

	return m;
}
