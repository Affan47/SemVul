collection_table_auto_scroll_idle_cb(gpointer data)
{
	CollectTable *ct = data;
	GdkWindow *window;
	gint x, y;
	gint w, h;

	if (!ct->drop_idle_id) return FALSE;

	window = ct->listview->window;
	gdk_window_get_pointer(window, &x, &y, NULL);
	gdk_drawable_get_size(window, &w, &h);
	if (x >= 0 && x < w && y >= 0 && y < h)
		{
		collection_table_motion_update(ct, x, y, TRUE);
		}

	ct->drop_idle_id = 0;
	return FALSE;
}
