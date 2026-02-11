ide_cdrom_capacity(ide_drive_t *drive)
{
	unsigned long capacity, sectors_per_frame;

	if (cdrom_read_capacity(drive, &capacity, &sectors_per_frame, NULL))
		return 0;

	return capacity * sectors_per_frame;
}
