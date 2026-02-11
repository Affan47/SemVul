suunto_vyper_send (suunto_vyper_device_t *device, const unsigned char command[], unsigned int csize)
{
	dc_device_t *abstract = (dc_device_t *) device;

	serial_sleep (device->port, 500);


	serial_set_rts (device->port, 1);


	int n = serial_write (device->port, command, csize);
	if (n != csize) {
		ERROR (abstract->context, "Failed to send the command.");
		return EXITCODE (n);
	}


	serial_sleep (device->port, 200);
	serial_flush (device->port, SERIAL_QUEUE_INPUT);


	serial_set_rts (device->port, 0);

	return DC_STATUS_SUCCESS;
}
