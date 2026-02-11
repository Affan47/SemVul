on_geany_sidebar_switch_page(G_GNUC_UNUSED GtkNotebook *notebook, gpointer page,
	G_GNUC_UNUSED gint page_num, G_GNUC_UNUSED gpointer gdata)
{
	if (page == inspect_page)
		view_inspect_update();
}
