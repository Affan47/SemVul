ide_disk_flush(ide_drive_t *drive)
{
	if (ata_id_flush_enabled(drive->id) == 0 ||
	    (drive->dev_flags & IDE_DFLAG_WCACHE) == 0)
		return;

	if (do_idedisk_flushcache(drive))
		printk(KERN_INFO "%s: wcache flush failed!\n", drive->name);
}
