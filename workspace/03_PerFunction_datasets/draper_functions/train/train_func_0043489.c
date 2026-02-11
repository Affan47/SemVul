ao_hex_checksum(struct ao_hex_record *record)
{
	uint8_t	checksum = 0;
	int i;

	checksum += record->length;
	checksum += record->address >> 8;
	checksum += record->address & 0xff;
	checksum += record->type;
	for (i = 0; i < record->length; i++)
		checksum += record->data[i];
	return -checksum;
}
