eel_canvas_item_ungrab (EelCanvasItem *item, guint32 etime)
{
	GdkDisplay *display;
	GdkDeviceManager *manager;
	GdkDevice *device;

	g_return_if_fail (EEL_IS_CANVAS_ITEM (item));

	if (item->canvas->grabbed_item != item)
		return;

	display = gtk_widget_get_display (GTK_WIDGET (item->canvas));
	manager = gdk_display_get_device_manager (display);
	device = gdk_device_manager_get_client_pointer (manager);

	item->canvas->grabbed_item = NULL;
	gdk_device_ungrab (device, etime);
}
