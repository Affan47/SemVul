slic_eeprom_cksum(void *eeprom, unsigned len)
{
	u16 *wp = eeprom;
	u32 checksum = 0;

	while (len > 1) {
		checksum += *(wp++);
		len -= 2;
	}

	if (len > 0)
		checksum += *(u8 *)wp;

	while (checksum >> 16)
		checksum = (checksum & 0xFFFF) + ((checksum >> 16) & 0xFFFF);

	return ~checksum;
}
