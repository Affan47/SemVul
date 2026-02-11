sht15_send_byte(struct sht15_data *data, u8 byte)
{
	int i;

	for (i = 0; i < 8; i++) {
		sht15_send_bit(data, !!(byte & 0x80));
		byte <<= 1;
	}
}
