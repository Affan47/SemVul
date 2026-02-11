ide_port_wait_ready(ide_hwif_t *hwif)
{
	const struct ide_tp_ops *tp_ops = hwif->tp_ops;
	ide_drive_t *drive;
	int i, rc;

	printk(KERN_DEBUG "Probing IDE interface %s...\n", hwif->name);


	mdelay(2);


	rc = ide_wait_not_busy(hwif, 35000);
	if (rc)
		return rc;


	ide_port_for_each_dev(i, drive, hwif) {

		if ((drive->dev_flags & IDE_DFLAG_NOPROBE) == 0 ||
		    (drive->dev_flags & IDE_DFLAG_PRESENT)) {
			tp_ops->dev_select(drive);
			tp_ops->write_devctl(hwif, ATA_DEVCTL_OBS);
			mdelay(2);
			rc = ide_wait_not_busy(hwif, 35000);
			if (rc)
				goto out;
		} else
			printk(KERN_DEBUG "%s: ide_wait_not_busy() skipped\n",
					  drive->name);
	}
out:

	if (i)
		tp_ops->dev_select(hwif->devices[0]);

	return rc;
}
