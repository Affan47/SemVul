mares_iconhd_device_open (dc_device_t **out, dc_context_t *context, const char *name, unsigned int model)
{
	if (out == NULL)
		return DC_STATUS_INVALIDARGS;


	mares_iconhd_device_t *device = (mares_iconhd_device_t *) malloc (sizeof (mares_iconhd_device_t));
	if (device == NULL) {
		ERROR (context, "Failed to allocate memory.");
		return DC_STATUS_NOMEMORY;
	}


	device_init (&device->base, context, &mares_iconhd_device_vtable);


	device->port = NULL;
	memset (device->fingerprint, 0, sizeof (device->fingerprint));
	memset (device->version, 0, sizeof (device->version));
	if (model == NEMOWIDE2 || model == MATRIX || model == PUCKPRO) {
		device->layout = &mares_matrix_layout;
		device->packetsize = 64;
	} else {
		device->layout = &mares_iconhd_layout;
		device->packetsize = 0;
	}


	int rc = serial_open (&device->port, context, name);
	if (rc == -1) {
		ERROR (context, "Failed to open the serial port.");
		free (device);
		return DC_STATUS_IO;
	}


	if (model == NEMOWIDE2 || model == MATRIX || model == PUCKPRO) {
		rc = serial_configure (device->port, 115200, 8, SERIAL_PARITY_EVEN, 1, SERIAL_FLOWCONTROL_NONE);
	} else {
		rc = serial_configure (device->port, BAUDRATE, 8, SERIAL_PARITY_NONE, 1, SERIAL_FLOWCONTROL_NONE);
	}
	if (rc == -1) {
		ERROR (context, "Failed to set the terminal attributes.");
		serial_close (device->port);
		free (device);
		return DC_STATUS_IO;
	}


	if (serial_set_timeout (device->port, 1000) == -1) {
		ERROR (context, "Failed to set the timeout.");
		serial_close (device->port);
		free (device);
		return DC_STATUS_IO;
	}


	if (serial_set_dtr (device->port, 0) == -1 ||
		serial_set_rts (device->port, 0) == -1)
	{
		ERROR (context, "Failed to set the DTR/RTS line.");
		serial_close (device->port);
		free (device);
		return DC_STATUS_IO;
	}


	serial_flush (device->port, SERIAL_QUEUE_BOTH);


	dc_status_t status = mares_iconhd_version (device, device->version, sizeof (device->version));
	if (status != DC_STATUS_SUCCESS) {
		serial_close (device->port);
		free (device);
		return status;
	}

	*out = (dc_device_t *) device;

	return DC_STATUS_SUCCESS;
}
