nand_wait_status_ready(struct mtd_info *mtd, unsigned long timeo)
{
	register struct nand_chip *chip = mtd->priv;

	timeo = jiffies + msecs_to_jiffies(timeo);
	do {
		if ((chip->read_byte(mtd) & NAND_STATUS_READY))
			break;
		touch_softlockup_watchdog();
	} while (time_before(jiffies, timeo));
}
