suunto_eon_device_write_interval (dc_device_t *abstract, unsigned char interval)
{
	suunto_eon_device_t *device = (suunto_eon_device_t*) abstract;

	if (!ISINSTANCE (abstract))
		return DC_STATUS_INVALIDARGS;


	unsigned char command[2] = {'T', interval};
	int rc = serial_write (device->port, command, sizeof (command));
	if (rc != sizeof (command)) {
		ERROR (abstract->context, "Failed to send the command.");
		return EXITCODE (rc);
	}

	return DC_STATUS_SUCCESS;
}
