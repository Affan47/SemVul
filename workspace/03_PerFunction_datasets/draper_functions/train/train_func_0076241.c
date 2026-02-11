hw_ostc_device_open (dc_device_t **out, dc_context_t *context, const char *name)
{
	if (out == NULL)
		return DC_STATUS_INVALIDARGS;


	hw_ostc_device_t *device = (hw_ostc_device_t *) malloc (sizeof (hw_ostc_device_t));
	if (device == NULL) {
		ERROR (context, "Failed to allocate memory.");
		return DC_STATUS_NOMEMORY;
	}


	device_init (&device->base, context, &hw_ostc_device_vtable);


	device->port = NULL;
	memset (device->fingerprint, 0, sizeof (device->fingerprint));


	int rc = serial_open (&device->port, context, name);
	if (rc == -1) {
		ERROR (context, "Failed to open the serial port.");
		free (device);
		return DC_STATUS_IO;
	}


	rc = serial_configure (device->port, 115200, 8, SERIAL_PARITY_NONE, 1, SERIAL_FLOWCONTROL_NONE);
	if (rc == -1) {
		ERROR (context, "Failed to set the terminal attributes.");
		serial_close (device->port);
		free (device);
		return DC_STATUS_IO;
	}


	if (serial_set_timeout (device->port, 4000) == -1) {
		ERROR (context, "Failed to set the timeout.");
		serial_close (device->port);
		free (device);
		return DC_STATUS_IO;
	}


	serial_sleep (device->port, 100);
	serial_flush (device->port, SERIAL_QUEUE_BOTH);

	*out = (dc_device_t*) device;

	return DC_STATUS_SUCCESS;
}
