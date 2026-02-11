mpxCRC(uint16_t crc, uint8_t value) {
	uint8_t i;

	crc = crc ^ (int16_t)value<<8;

	for (i = 0; i < 8; i++) {
		if (crc & 0x8000) {
			crc = crc << 1^0x1021;
		} else {
			crc = crc << 1;
		}
	}

	return crc;
}
