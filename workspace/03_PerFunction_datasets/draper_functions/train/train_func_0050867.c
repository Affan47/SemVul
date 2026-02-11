plugin_finish()
{
	while (plugin_info.prefs) {
		input_list *il = plugin_info.prefs->next;
		g_free(plugin_info.prefs);
		plugin_info.prefs = il;
	}

	if (mi1)
		eb_remove_menu_item(EB_CHAT_WINDOW_MENU, mi1);
	if (mi2)
		eb_remove_menu_item(EB_CONTACT_MENU, mi2);
	mi1 = NULL;
	mi2 = NULL;
	eb_debug(DBG_MSN, "Returning the ref_count: %i\n", ref_count);
	return (ref_count);
}
