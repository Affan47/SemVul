_e2_toolbar_update_style_cb (GtkWidget *menuitem, E2_ToolbarRuntime *rt)
{
	if (!rt->blocked)
	{
		GSList *group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
		gint index = 4 - g_slist_index (group, menuitem);
		if (e2_option_int_get_direct (rt->style) != index)
		{
			e2_option_sel_set_direct (rt->style, index);
			e2_toolbar_recreate (rt);
		}
	}
}
