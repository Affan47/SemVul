wdt_open(struct inode *inode, struct file *file)
{
	if (MINOR(inode->i_rdev) == WATCHDOG_MINOR) {
		mutex_lock(&m41t80_rtc_mutex);
		if (test_and_set_bit(0, &wdt_is_open)) {
			mutex_unlock(&m41t80_rtc_mutex);
			return -EBUSY;
		}


		wdt_is_open = 1;
		mutex_unlock(&m41t80_rtc_mutex);
		return nonseekable_open(inode, file);
	}
	return -ENODEV;
}
