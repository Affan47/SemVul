gusb_cmd_show (GUsbCmdPrivate *priv, gchar **values, GError **error)
{
	gboolean ret = TRUE;
	GPtrArray *devices;
	guint i;
	GUsbDevice *device;
	GUsbDeviceList *list;

	list = g_usb_device_list_new (priv->usb_ctx);
	g_usb_device_list_coldplug (list);
	devices = g_usb_device_list_get_devices (list);
	for (i=0; i<devices->len; i++) {
		device = g_ptr_array_index (devices, i);
		g_print ("device present %x:%x\n",
			 g_usb_device_get_bus (device),
			 g_usb_device_get_address (device));
	}
	g_ptr_array_unref (devices);
	if (list != NULL)
		g_object_unref (list);
	return ret;
}
