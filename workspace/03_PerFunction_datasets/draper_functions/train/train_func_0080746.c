reefnet_sensus_cancel (reefnet_sensus_device_t *device)
{
	dc_device_t *abstract = (dc_device_t *) device;


	unsigned char command = 0x00;
	int n = serial_write (device->port, &command, 1);
	if (n != 1) {
		ERROR (abstract->context, "Failed to send the command.");
		return EXITCODE (n);
	}


	device->waiting = 0;

	return DC_STATUS_SUCCESS;
}
