reefnet_sensusultra_device_get_handshake (dc_device_t *abstract, unsigned char data[], unsigned int size)
{
	reefnet_sensusultra_device_t *device = (reefnet_sensusultra_device_t*) abstract;

	if (!ISINSTANCE (abstract))
		return DC_STATUS_INVALIDARGS;

	if (size < SZ_HANDSHAKE) {
		ERROR (abstract->context, "Insufficient buffer space available.");
		return DC_STATUS_INVALIDARGS;
	}

	memcpy (data, device->handshake, SZ_HANDSHAKE);

	return DC_STATUS_SUCCESS;
}
