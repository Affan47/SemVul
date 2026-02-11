vf_pop_menu_toggle_view_type_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;
	FileViewType new_type = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "menu_item_radio_data"));
	if (!vf->layout) return;

	layout_views_set(vf->layout, vf->layout->options.dir_view_type, new_type);
}
