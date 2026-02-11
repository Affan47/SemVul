mares_puck_device_open (dc_device_t **out, dc_context_t *context, const char *name)
{
	if (out == NULL)
		return DC_STATUS_INVALIDARGS;


	mares_puck_device_t *device = (mares_puck_device_t *) malloc (sizeof (mares_puck_device_t));
	if (device == NULL) {
		ERROR (context, "Failed to allocate memory.");
		return DC_STATUS_NOMEMORY;
	}


	mares_common_device_init (&device->base, context, &mares_puck_device_vtable);


	device->layout = NULL;
	memset (device->fingerprint, 0, sizeof (device->fingerprint));


	int rc = serial_open (&device->base.port, context, name);
	if (rc == -1) {
		ERROR (context, "Failed to open the serial port.");
		free (device);
		return DC_STATUS_IO;
	}


	rc = serial_configure (device->base.port, 38400, 8, SERIAL_PARITY_NONE, 1, SERIAL_FLOWCONTROL_NONE);
	if (rc == -1) {
		ERROR (context, "Failed to set the terminal attributes.");
		serial_close (device->base.port);
		free (device);
		return DC_STATUS_IO;
	}


	if (serial_set_timeout (device->base.port, 1000) == -1) {
		ERROR (context, "Failed to set the timeout.");
		serial_close (device->base.port);
		free (device);
		return DC_STATUS_IO;
	}


	if (serial_set_dtr (device->base.port, 0) == -1 ||
		serial_set_rts (device->base.port, 0) == -1) {
		ERROR (context, "Failed to set the DTR/RTS line.");
		serial_close (device->base.port);
		free (device);
		return DC_STATUS_IO;
	}


	serial_flush (device->base.port, SERIAL_QUEUE_BOTH);


	unsigned char header[PACKETSIZE] = {0};
	dc_status_t status = mares_common_device_read ((dc_device_t *) device, 0, header, sizeof (header));
	if (status != DC_STATUS_SUCCESS) {
		serial_close (device->base.port);
		free (device);
		return status;
	}


	switch (header[1]) {
	case NEMOWIDE:
		device->layout = &mares_nemowide_layout;
		break;
	case NEMOAIR:
	case PUCKAIR:
		device->layout = &mares_nemoair_layout;
		break;
	case PUCK:
		device->layout = &mares_puck_layout;
		break;
	default:
		device->layout = &mares_puck_layout;
		break;
	}

	*out = (dc_device_t*) device;

	return DC_STATUS_SUCCESS;
}
