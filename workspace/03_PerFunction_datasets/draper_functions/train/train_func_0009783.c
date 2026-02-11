oceanic_atom2_device_keepalive (dc_device_t *abstract)
{
	oceanic_atom2_device_t *device = (oceanic_atom2_device_t*) abstract;

	if (!ISINSTANCE (abstract))
		return DC_STATUS_INVALIDARGS;


	unsigned char command[4] = {0x91, 0x05, 0xA5, 0x00};
	dc_status_t rc = oceanic_atom2_transfer (device, command, sizeof (command), NULL, 0);
	if (rc != DC_STATUS_SUCCESS)
		return rc;

	return DC_STATUS_SUCCESS;
}
