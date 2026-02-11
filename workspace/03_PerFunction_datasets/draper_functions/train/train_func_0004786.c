crc32(const void *buf, size_t size)
{
	const uint8_t *p;
	uint32_t crc;

	p = buf;
	crc = ~0U;

	while (size--)
		crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);

	return crc ^ ~0U;
}
