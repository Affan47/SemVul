__ide_wait_stat(ide_drive_t *drive, u8 good, u8 bad,
		    unsigned long timeout, u8 *rstat)
{
	ide_hwif_t *hwif = drive->hwif;
	const struct ide_tp_ops *tp_ops = hwif->tp_ops;
	unsigned long flags;
	int i;
	u8 stat;

	udelay(1);
	stat = tp_ops->read_status(hwif);

	if (stat & ATA_BUSY) {
		local_save_flags(flags);
		local_irq_enable_in_hardirq();
		timeout += jiffies;
		while ((stat = tp_ops->read_status(hwif)) & ATA_BUSY) {
			if (time_after(jiffies, timeout)) {


				stat = tp_ops->read_status(hwif);
				if ((stat & ATA_BUSY) == 0)
					break;

				local_irq_restore(flags);
				*rstat = stat;
				return -EBUSY;
			}
		}
		local_irq_restore(flags);
	}


	for (i = 0; i < 10; i++) {
		udelay(1);
		stat = tp_ops->read_status(hwif);

		if (OK_STAT(stat, good, bad)) {
			*rstat = stat;
			return 0;
		}
	}
	*rstat = stat;
	return -EFAULT;
}
