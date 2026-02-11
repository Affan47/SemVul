unexpected_intr(int irq, ide_hwif_t *hwif)
{
	u8 stat = hwif->tp_ops->read_status(hwif);

	if (!OK_STAT(stat, ATA_DRDY, BAD_STAT)) {

		static unsigned long last_msgtime, count;
		++count;

		if (time_after(jiffies, last_msgtime + HZ)) {
			last_msgtime = jiffies;
			printk(KERN_ERR "%s: unexpected interrupt, "
				"status=0x%02x, count=%ld\n",
				hwif->name, stat, count);
		}
	}
}
