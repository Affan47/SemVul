reefnet_sensusultra_send_ushort (reefnet_sensusultra_device_t *device, unsigned short value)
{

	unsigned char lsb = value & 0xFF;
	dc_status_t rc = reefnet_sensusultra_send_uchar (device, lsb);
	if (rc != DC_STATUS_SUCCESS)
		return rc;


	unsigned char msb = (value >> 8) & 0xFF;
	rc = reefnet_sensusultra_send_uchar (device, msb);
	if (rc != DC_STATUS_SUCCESS)
		return rc;

	return DC_STATUS_SUCCESS;
}
