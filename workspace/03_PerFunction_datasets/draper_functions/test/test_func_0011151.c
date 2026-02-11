reefnet_sensusultra_device_write_user (dc_device_t *abstract, const unsigned char *data, unsigned int size)
{
	reefnet_sensusultra_device_t *device = (reefnet_sensusultra_device_t*) abstract;

	if (!ISINSTANCE (abstract))
		return DC_STATUS_INVALIDARGS;

	if (size < SZ_USER) {
		ERROR (abstract->context, "Insufficient buffer space available.");
		return DC_STATUS_INVALIDARGS;
	}


	dc_event_progress_t progress = EVENT_PROGRESS_INITIALIZER;
	progress.maximum = SZ_USER + 2;
	device_event_emit (abstract, DC_EVENT_PROGRESS, &progress);


	dc_status_t rc = reefnet_sensusultra_send (device, 0xB430);
	if (rc != DC_STATUS_SUCCESS)
		return rc;


	for (unsigned int i = 0; i < SZ_USER; ++i) {
		rc = reefnet_sensusultra_send_uchar (device, data[i]);
		if (rc != DC_STATUS_SUCCESS)
			return rc;


		progress.current += 1;
		device_event_emit (abstract, DC_EVENT_PROGRESS, &progress);
	}


	unsigned short crc = checksum_crc_ccitt_uint16 (data, SZ_USER);
	rc = reefnet_sensusultra_send_ushort (device, crc);
	if (rc != DC_STATUS_SUCCESS)
		return rc;


	progress.current += 2;
	device_event_emit (abstract, DC_EVENT_PROGRESS, &progress);

	return DC_STATUS_SUCCESS;
}
