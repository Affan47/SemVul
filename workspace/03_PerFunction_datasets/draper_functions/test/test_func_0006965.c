cressi_edy_device_read (dc_device_t *abstract, unsigned int address, unsigned char data[], unsigned int size)
{
	cressi_edy_device_t *device = (cressi_edy_device_t*) abstract;

	if ((address % SZ_PAGE != 0) ||
		(size    % SZ_PACKET != 0))
		return DC_STATUS_INVALIDARGS;

	unsigned int nbytes = 0;
	while (nbytes < size) {

		unsigned int number = address / SZ_PAGE;
		unsigned char answer[3 + SZ_PACKET + 1] = {0};
		unsigned char command[3] = {0x52,
				(number >> 8) & 0xFF,
				(number     ) & 0xFF};
		dc_status_t rc = cressi_edy_transfer (device, command, sizeof (command), answer, sizeof (answer), 1);
		if (rc != DC_STATUS_SUCCESS)
			return rc;

		memcpy (data, answer + 3, SZ_PACKET);

		nbytes += SZ_PACKET;
		address += SZ_PACKET;
		data += SZ_PACKET;
	}

	return DC_STATUS_SUCCESS;
}
