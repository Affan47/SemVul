atadev_read_capacity ( struct ata_device *atadev,
				  struct interface *block ) {
	struct ata_identity *identity;

	assert ( atacmd_identify.priv_len == sizeof ( *identity ) );
	assert ( atacmd_identify.priv_len == ATA_SECTOR_SIZE );
	return atadev_command ( atadev, block, &atacmd_identify,
				0, 1, UNULL, ATA_SECTOR_SIZE );
}
