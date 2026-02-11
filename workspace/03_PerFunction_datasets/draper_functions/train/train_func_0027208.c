find_notebook_at_pointer (gint abs_x, gint abs_y)
{
	GdkDeviceManager *manager;
	GdkDevice *pointer;
	GdkWindow *win_at_pointer, *toplevel_win;
	gpointer toplevel = NULL;
	gint x, y;


	manager = gdk_display_get_device_manager (gdk_display_get_default ());
	pointer = gdk_device_manager_get_client_pointer (manager);
	win_at_pointer = gdk_device_get_window_at_position (pointer, &x, &y);

	if (win_at_pointer == NULL)
	{

		return NULL;
	}

	toplevel_win = gdk_window_get_toplevel (win_at_pointer);


	gdk_window_get_user_data (toplevel_win, &toplevel);


	if (toplevel != NULL && NAUTILUS_IS_WINDOW (toplevel))
	{
		return NAUTILUS_NOTEBOOK (NAUTILUS_WINDOW (toplevel)->details->notebook);
	}

	return NULL;
}
