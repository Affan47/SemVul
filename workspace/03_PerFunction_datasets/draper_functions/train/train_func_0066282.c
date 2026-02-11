xmms_samba_destroy (xmms_xform_t *xform)
{
	gint err;
	xmms_samba_data_t *data;

	g_return_if_fail (xform);
	data = xmms_xform_private_data_get (xform);
	g_return_if_fail (data);

	if (data->fd != -1) {
		g_static_mutex_lock (&mutex);
		err = smbc_close (data->fd);
		g_static_mutex_unlock (&mutex);

		if (err < 0) {
			xmms_log_error ("%s", strerror (errno));
		}
	}

	g_free (data);
}
