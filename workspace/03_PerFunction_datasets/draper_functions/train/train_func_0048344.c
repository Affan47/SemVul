mpk_compute_crc(UINT32 crc, size_t len, void *buffer) {
	unsigned char *p = (unsigned char*)buffer;
	while(len-- != 0) {
		UINT32 tmp1 = (crc >> 8) & 0x00FFFFFFL;
		UINT32 tmp2 = mpk_crc_table[((int)crc ^ *p++) & 0xFF];
		crc = tmp1 ^ tmp2;
	}

	return crc;
}
