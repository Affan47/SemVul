mg_create_tab_colors (void)
{
	if (plain_list)
	{
		pango_attr_list_unref (plain_list);
		pango_attr_list_unref (newmsg_list);
		pango_attr_list_unref (newdata_list);
		pango_attr_list_unref (nickseen_list);
		pango_attr_list_unref (away_list);
	}

	plain_list = mg_attr_list_create (NULL, prefs.hex_gui_tab_small);
	newdata_list = mg_attr_list_create (&colors[COL_NEW_DATA], prefs.hex_gui_tab_small);
	nickseen_list = mg_attr_list_create (&colors[COL_HILIGHT], prefs.hex_gui_tab_small);
	newmsg_list = mg_attr_list_create (&colors[COL_NEW_MSG], prefs.hex_gui_tab_small);
	away_list = mg_attr_list_create (&colors[COL_AWAY], FALSE);
}
