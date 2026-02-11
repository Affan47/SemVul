impl_device_disconnect (NMDevice *device, DBusGMethodInvocation *context)
{
	GError *error = NULL;

	if (NM_DEVICE_GET_PRIVATE (device)->act_request == NULL) {
		error = g_error_new_literal (NM_DEVICE_ERROR,
		                             NM_DEVICE_ERROR_NOT_ACTIVE,
		                             "This device is not active");
		dbus_g_method_return_error (context, error);
		g_error_free (error);
		return;
	}


	g_signal_emit (device, signals[AUTH_REQUEST], 0,
	               context,
	               NM_AUTH_PERMISSION_NETWORK_CONTROL,
	               TRUE,
	               disconnect_cb,
	               NULL);
}
