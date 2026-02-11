huey_device_read_register_vector (GUsbDevice *device,
				  guint8 addr,
				  CdVec3 *value,
				  GError **error)
{
	gboolean ret = TRUE;
	guint i;
	gfloat tmp = 0.0f;
	gdouble *vector_data;

	g_return_val_if_fail (G_USB_IS_DEVICE (device), FALSE);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);


	vector_data = cd_vec3_get_data (value);


	for (i = 0; i < 3; i++) {
		ret = huey_device_read_register_float (device,
						       addr + (i*4),
						       &tmp,
						       error);
		if (!ret)
			goto out;


		*(vector_data+i) = tmp;
	}
out:
	return ret;
}
