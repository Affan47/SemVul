ide_floppy_get_flexible_disk_page(ide_drive_t *drive,
					     struct ide_atapi_pc *pc)
{
	struct ide_disk_obj *floppy = drive->driver_data;
	struct gendisk *disk = floppy->disk;
	u8 *page, buf[40];
	int capacity, lba_capacity;
	u16 transfer_rate, sector_size, cyls, rpm;
	u8 heads, sectors;

	ide_floppy_create_mode_sense_cmd(pc, IDEFLOPPY_FLEXIBLE_DISK_PAGE);

	if (ide_queue_pc_tail(drive, disk, pc, buf, pc->req_xfer)) {
		printk(KERN_ERR PFX "Can't get flexible disk page params\n");
		return 1;
	}

	if (buf[3] & 0x80)
		drive->dev_flags |= IDE_DFLAG_WP;
	else
		drive->dev_flags &= ~IDE_DFLAG_WP;

	set_disk_ro(disk, !!(drive->dev_flags & IDE_DFLAG_WP));

	page = &buf[8];

	transfer_rate = be16_to_cpup((__be16 *)&buf[8 + 2]);
	sector_size   = be16_to_cpup((__be16 *)&buf[8 + 6]);
	cyls          = be16_to_cpup((__be16 *)&buf[8 + 8]);
	rpm           = be16_to_cpup((__be16 *)&buf[8 + 28]);
	heads         = buf[8 + 4];
	sectors       = buf[8 + 5];

	capacity = cyls * heads * sectors * sector_size;

	if (memcmp(page, &floppy->flexible_disk_page, 32))
		printk(KERN_INFO PFX "%s: %dkB, %d/%d/%d CHS, %d kBps, "
				"%d sector size, %d rpm\n",
				drive->name, capacity / 1024, cyls, heads,
				sectors, transfer_rate / 8, sector_size, rpm);

	memcpy(&floppy->flexible_disk_page, page, 32);
	drive->bios_cyl = cyls;
	drive->bios_head = heads;
	drive->bios_sect = sectors;
	lba_capacity = floppy->blocks * floppy->block_size;

	if (capacity < lba_capacity) {
		printk(KERN_NOTICE PFX "%s: The disk reports a capacity of %d "
			"bytes, but the drive only handles %d\n",
			drive->name, lba_capacity, capacity);
		floppy->blocks = floppy->block_size ?
			capacity / floppy->block_size : 0;
		drive->capacity64 = floppy->blocks * floppy->bs_factor;
	}

	return 0;
}
