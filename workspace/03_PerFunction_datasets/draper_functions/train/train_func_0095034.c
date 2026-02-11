nm_device_get_vendor (NMDevice *device)
{
	NMDevicePrivate *priv;

	g_return_val_if_fail (NM_IS_DEVICE (device), NULL);

	priv = NM_DEVICE_GET_PRIVATE (device);
	if (!priv->vendor) {
		priv->vendor = _get_udev_property (device, "ID_VENDOR_ENC", "ID_VENDOR_FROM_DATABASE");
		_nm_object_queue_notify (NM_OBJECT (device), NM_DEVICE_VENDOR);
	}
	return priv->vendor;
}
