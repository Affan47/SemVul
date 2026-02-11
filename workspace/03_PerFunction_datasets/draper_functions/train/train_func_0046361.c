CRC16(u_int8_t value, u_int16_t crcin)
{
    u_int16_t k = (((crcin >> 8) ^ value) & 255) << 8;
    u_int16_t crc = 0;
    int bits;
    for (bits = 8; bits; --bits) {
	if ((crc ^ k) & 0x8000)
	    crc = (crc << 1) ^ 0x1021;
	else
	    crc <<= 1;
	k <<= 1;
    }
    return ((crcin << 8) ^ crc);
}
