hidpp_device_read_resp (HidppDevice	*device,
			guchar		 device_index,
			guchar		 feature_index,
			guchar		 function_index,
			HidppMessage	*response,
			GError	**error)
{
	HidppDevicePrivate *priv = device->priv;
	gboolean ret = TRUE;
	gssize r;
	GPollFD poll[] = {
		{
			.fd = priv->fd,
			.events = G_IO_IN | G_IO_OUT | G_IO_ERR,
		},
	};
	guint64 begin_time;
	gint remaining_time;
	guchar error_code;


	begin_time = g_get_monotonic_time () / 1000;
	for (;;) {

		remaining_time = HIDPP_DEVICE_READ_RESPONSE_TIMEOUT -
			(g_get_monotonic_time () / 1000 - begin_time);
		if (remaining_time <= 0) {
			g_set_error (error, 1, 0,
					"timeout while reading response");
			ret = FALSE;
			goto out;
		}

		r = g_poll (poll, G_N_ELEMENTS(poll), remaining_time);
		if (r < 0) {
			if (errno == EINTR)
				continue;

			g_set_error (error, 1, 0,
					"Failed to read from device: %s",
					g_strerror (errno));
			ret = FALSE;
			goto out;
		} else if (r == 0) {
			g_set_error (error, 1, 0,
					"Attempt to read response from device timed out");
			ret = FALSE;
			goto out;
		}

		r = read (priv->fd, response, sizeof (*response));
		if (r <= 0) {
			if (r == -1 && errno == EINTR)
				continue;

			g_set_error (error, 1, 0,
					"Unable to read response from device: %s",
					g_strerror (errno));
			ret = FALSE;
			goto out;
		}

		hidpp_device_print_buffer (device, response);


		if (response->type != HIDPP_MSG_TYPE_SHORT &&
			response->type != HIDPP_MSG_TYPE_LONG) {

			continue;
		}


		if (response->device_idx != device_index) {
			continue;
		}


		if (response->feature_idx == feature_index &&
			response->function_idx == function_index) {
			break;
		}


		if (hidpp_is_error(response, &error_code) &&
			response->function_idx == feature_index &&
			response->s.params[0] == function_index) {
			g_set_error (error, 1, 0,
				"Unable to satisfy request, HID++ error %02x", error_code);
			ret = FALSE;
			goto out;
		}


	}

out:
	return ret;
}
