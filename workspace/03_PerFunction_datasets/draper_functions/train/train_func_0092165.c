pl3_find2_browser_connection_changed(MpdObj * mi, int connect, gpointer data)
{

	if (connect)
	{
		if (pl3_find2_curpl)
			pl3_find2_browser_type_plugin_changed(GTK_COMBO_BOX(pl3_find2_curpl), NULL);
		pl3_find2_browser_search();
	}
}
