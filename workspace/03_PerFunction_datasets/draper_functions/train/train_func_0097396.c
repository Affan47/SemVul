int13_get_extended_parameters ( struct int13_drive *drive,
					   struct i386_all_regs *ix86 ) {
	struct int13_disk_parameters params = {
		.bufsize = sizeof ( params ),
		.flags = INT13_FL_DMA_TRANSPARENT,
		.cylinders = drive->cylinders,
		.heads = drive->heads,
		.sectors_per_track = drive->sectors_per_track,
		.sectors = drive->blockdev->blocks,
		.sector_size = drive->blockdev->blksize,
	};

	DBG ( "Get extended drive parameters to %04x:%04x\n",
	      ix86->segs.ds, ix86->regs.si );

	copy_to_real ( ix86->segs.ds, ix86->regs.si, &params,
		       sizeof ( params ) );
	return 0;
}
