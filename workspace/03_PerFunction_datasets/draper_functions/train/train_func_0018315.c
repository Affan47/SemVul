g_supplicant_interface_remove(GSupplicantInterface *interface,
			GSupplicantInterfaceCallback callback,
							void *user_data)
{
	struct interface_data *data;

	if (interface == NULL)
		return -EINVAL;

	if (system_available == FALSE)
		return -EFAULT;

	data = dbus_malloc0(sizeof(*data));
	if (data == NULL)
		return -ENOMEM;

	data->interface = interface;
	data->callback = callback;
	data->user_data = user_data;

	return supplicant_dbus_method_call(SUPPLICANT_PATH,
						SUPPLICANT_INTERFACE,
						"RemoveInterface",
						interface_remove_params,
						interface_remove_result, data);
}
