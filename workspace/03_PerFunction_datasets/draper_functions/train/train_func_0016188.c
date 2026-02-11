get_x_content_async_callback (const char **content,
			      gpointer user_data)
{
	NautilusView *view;

	view = NAUTILUS_VIEW (user_data);

	if (view->details->slot != NULL) {
		schedule_update_menus (view);
	}
	g_object_unref (view);
}
