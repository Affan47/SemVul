zpodd_on_suspend(struct ata_device *dev)
{
	struct zpodd *zpodd = dev->zpodd;
	unsigned long expires;

	if (!zpready(dev)) {
		zpodd->zp_sampled = false;
		zpodd->zp_ready = false;
		return;
	}

	if (!zpodd->zp_sampled) {
		zpodd->zp_sampled = true;
		zpodd->last_ready = jiffies;
		return;
	}

	expires = zpodd->last_ready +
		  msecs_to_jiffies(zpodd_poweroff_delay * 1000);
	if (time_before(jiffies, expires))
		return;

	zpodd->zp_ready = true;
}
