Write(uint8_t typ, uint8_t cmd, uint32_t len,
	uint8_t *data)
{
	if (len > USBNET_MAX_PACKET_SIZE) {
		return LC_ERROR;
	}

	static const uint8_t service_type = SERVICE_FAMILY_CLIENT;
	const bool request = (typ == TYPE_REQUEST);
	const uint8_t status = STATUS_OK;

	uint8_t pkt[USBNET_MAX_PACKET_SIZE+3];
	pkt[0] = service_type << 4 | (cmd >> 8) & 0x0F;
	pkt[1] = cmd & 0xFF;
	pkt[2] = request ? 0x80 : (status & 0x7F);

	if (len && data) {
		memcpy(pkt + 3, data, len);
		len += 3;
	} else {
		pkt[3] = 0x00;
		len = 4;
	}

	return UsbLan_Write(len, pkt);
}
