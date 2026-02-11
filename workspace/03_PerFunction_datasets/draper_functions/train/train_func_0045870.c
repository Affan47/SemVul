FLAC__crc8_update_block(const FLAC__byte *data, unsigned len, FLAC__uint8 *crc)
{
	while(len--)
		*crc = FLAC__crc8_table[*crc ^ *data++];
}
