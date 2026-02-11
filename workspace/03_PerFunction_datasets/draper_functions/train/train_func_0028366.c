int13_extended_rw ( struct int13_drive *drive,
			       struct i386_all_regs *ix86,
			       int ( * io ) ( struct block_device *blockdev,
					      uint64_t block,
					      unsigned long count,
					      userptr_t buffer ) ) {
	struct block_device *blockdev = drive->blockdev;
	struct int13_disk_address addr;
	uint64_t lba;
	unsigned long count;
	userptr_t buffer;
	int rc;


	copy_from_real ( &addr, ix86->segs.ds, ix86->regs.si, sizeof ( addr ));
	lba = addr.lba;
	count = addr.count;
	buffer = real_to_user ( addr.buffer.segment, addr.buffer.offset );

	DBG ( "LBA %#llx <-> %04x:%04x (count %ld)\n", (unsigned long long)lba,
	      addr.buffer.segment, addr.buffer.offset, count );


	if ( ( rc = io ( blockdev, lba, count, buffer ) ) != 0 ) {
		DBG ( "INT 13 failed: %s\n", strerror ( rc ) );
		return -INT13_STATUS_READ_ERROR;
	}

	return 0;
}
