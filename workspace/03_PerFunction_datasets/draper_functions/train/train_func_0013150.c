volume_id_set_unicode16(uint8_t *str, size_t len, const uint8_t *buf, enum endian endianess, size_t count)
{
	size_t i, j;
	uint16_t c;

	j = 0;
	for (i = 0; i + 2 <= count; i += 2) {
		if (endianess == LE)
			c = (buf[i+1] << 8) | buf[i];
		else
			c = (buf[i] << 8) | buf[i+1];
		if (c == 0) {
			str[j] = '\0';
			break;
		} else if (c < 0x80) {
			if (j+1 >= len)
				break;
			str[j++] = (uint8_t) c;
		} else if (c < 0x800) {
			if (j+2 >= len)
				break;
			str[j++] = (uint8_t) (0xc0 | (c >> 6));
			str[j++] = (uint8_t) (0x80 | (c & 0x3f));
		} else {
			if (j+3 >= len)
				break;
			str[j++] = (uint8_t) (0xe0 | (c >> 12));
			str[j++] = (uint8_t) (0x80 | ((c >> 6) & 0x3f));
			str[j++] = (uint8_t) (0x80 | (c & 0x3f));
		}
	}
	str[j] = '\0';
	return j;
}
