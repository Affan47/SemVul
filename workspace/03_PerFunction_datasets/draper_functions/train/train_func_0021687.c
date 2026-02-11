exfat_add_checksum(const void* entry, uint16_t sum)
{
	int i;

	for (i = 0; i < sizeof(struct exfat_entry); i++)
		sum = ((sum << 15) | (sum >> 1)) + ((const uint8_t*) entry)[i];
	return sum;
}
