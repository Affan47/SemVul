LUKS_device_sectors(size_t keyLen)
{
	size_t keyslot_sectors, sector;
	int i;

	keyslot_sectors = AF_split_sectors(keyLen, LUKS_STRIPES);
	sector = LUKS_ALIGN_KEYSLOTS / SECTOR_SIZE;

	for (i = 0; i < LUKS_NUMKEYS; i++) {
		sector = size_round_up(sector, LUKS_ALIGN_KEYSLOTS / SECTOR_SIZE);
		sector += keyslot_sectors;
	}

	return sector;
}
