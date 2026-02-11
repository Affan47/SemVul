baytrail_i2c_acquire(struct dw_i2c_dev *dev)
{
	u32 sem;
	int ret;
	unsigned long start, end;

	might_sleep();

	if (!dev || !dev->dev)
		return -ENODEV;

	if (!dev->release_lock)
		return 0;


	ret = iosf_mbi_write(BT_MBI_UNIT_PMC, BT_MBI_BUNIT_WRITE,
				PUNIT_SEMAPHORE, PUNIT_SEMAPHORE_ACQUIRE);
	if (ret) {
		dev_err(dev->dev, "iosf punit semaphore request failed\n");
		return ret;
	}


	start = jiffies;
	end = start + msecs_to_jiffies(SEMAPHORE_TIMEOUT);
	do {
		ret = get_sem(dev->dev, &sem);
		if (!ret && sem) {
			acquired = jiffies;
			dev_dbg(dev->dev, "punit semaphore acquired after %ums\n",
				jiffies_to_msecs(jiffies - start));
			return 0;
		}

		usleep_range(1000, 2000);
	} while (time_before(jiffies, end));

	dev_err(dev->dev, "punit semaphore timed out, resetting\n");
	reset_semaphore(dev->dev);

	ret = iosf_mbi_read(BT_MBI_UNIT_PMC, BT_MBI_BUNIT_READ,
				PUNIT_SEMAPHORE, &sem);
	if (ret)
		dev_err(dev->dev, "iosf failed to read punit semaphore\n");
	else
		dev_err(dev->dev, "PUNIT SEM: %d\n", sem);

	WARN_ON(1);

	return -ETIMEDOUT;
}
