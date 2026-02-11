kb_activate(guint key_id)
{
	gchar *current_tag;

	switch (key_id)
	{
		case KB_DEVHELP_TOGGLE_CONTENTS:
			devhelp_plugin_toggle_contents_tab(plugin.devhelp);
			break;
		case KB_DEVHELP_TOGGLE_SEARCH:
			devhelp_plugin_toggle_search_tab(plugin.devhelp);
			break;
		case KB_DEVHELP_TOGGLE_WEBVIEW:
			devhelp_plugin_toggle_webview_tab(plugin.devhelp);
			break;
		case KB_DEVHELP_ACTIVATE_DEVHELP:
			devhelp_plugin_activate_all_tabs(plugin.devhelp);
			break;
		case KB_DEVHELP_SEARCH_SYMBOL:
		{
			current_tag = devhelp_plugin_get_current_word(plugin.devhelp);
			if (current_tag == NULL)
				return;
			devhelp_plugin_search_books(plugin.devhelp, current_tag);
			g_free(current_tag);
			break;
		}
		case KB_DEVHELP_SEARCH_MANPAGES:
		{
			current_tag = devhelp_plugin_get_current_word(plugin.devhelp);
			if (current_tag == NULL)
				return;
			devhelp_plugin_search_manpages(plugin.devhelp, current_tag);
			g_free(current_tag);
			break;
		}
	}
}
