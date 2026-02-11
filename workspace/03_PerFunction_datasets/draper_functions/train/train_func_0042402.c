init_mio(void)
{
	free(mio_rom);
	mio_rom = (UBYTE *)Util_malloc(mio_rom_size);
	if (!Atari800_LoadImage(mio_rom_filename, mio_rom, mio_rom_size)) {
		free(mio_rom);
		mio_rom = NULL;
		return;
	}
	D(printf("Loaded mio rom image\n"));
	PBI_MIO_enabled = TRUE;
	if (PBI_SCSI_disk != NULL) fclose(PBI_SCSI_disk);
	if (!Util_filenamenotset(mio_scsi_disk_filename)) {
		PBI_SCSI_disk = fopen(mio_scsi_disk_filename, "rb+");
		if (PBI_SCSI_disk == NULL) {
			Log_print("Error opening SCSI disk image:%s", mio_scsi_disk_filename);
		}
		else {
			D(printf("Opened SCSI disk image\n"));
			mio_scsi_enabled = TRUE;
		}
	}
	if (!mio_scsi_enabled) {
		PBI_SCSI_BSY = TRUE;
	}
	free(mio_ram);
	mio_ram = (UBYTE *)Util_malloc(mio_ram_size);
	memset(mio_ram, 0, mio_ram_size);
}
