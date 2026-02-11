up_device_get_online (UpDevice *device, gboolean *online)
{
	UpDeviceClass *klass = UP_DEVICE_GET_CLASS (device);

	g_return_val_if_fail (UP_IS_DEVICE (device), FALSE);


	if (klass->get_online == NULL)
		return FALSE;

	return klass->get_online (device, online);
}
