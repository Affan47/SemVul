ethi_drag_leave (GtkWidget *widget,
                 GdkDragContext *context,
                 guint time,
                 ETableHeaderItem *ethi)
{
	ethi_remove_drop_marker (ethi);
	if (ethi->drag_col != -1)
		ethi_add_destroy_marker (ethi);
}
