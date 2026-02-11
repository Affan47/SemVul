suunto_vyper_device_write (dc_device_t *abstract, unsigned int address, const unsigned char data[], unsigned int size)
{
	suunto_vyper_device_t *device = (suunto_vyper_device_t*) abstract;

	unsigned int nbytes = 0;
	while (nbytes < size) {

		unsigned int len = MIN (size - nbytes, SZ_PACKET);


		unsigned char panswer[3] = {0};
		unsigned char pcommand[3] = {0x07, 0xA5, 0xA2};
		dc_status_t rc = suunto_vyper_transfer (device, pcommand, sizeof (pcommand), panswer, sizeof (panswer), 0);
		if (rc != DC_STATUS_SUCCESS)
			return rc;


		unsigned char wanswer[5] = {0};
		unsigned char wcommand[SZ_PACKET + 5] = {0x06,
				(address >> 8) & 0xFF,
				(address     ) & 0xFF,
				len,
				0};
		memcpy (wcommand + 4, data, len);
		wcommand[len + 4] = checksum_xor_uint8 (wcommand, len + 4, 0x00);
		rc = suunto_vyper_transfer (device, wcommand, len + 5, wanswer, sizeof (wanswer), 0);
		if (rc != DC_STATUS_SUCCESS)
			return rc;

		nbytes += len;
		address += len;
		data += len;
	}

	return DC_STATUS_SUCCESS;
}
