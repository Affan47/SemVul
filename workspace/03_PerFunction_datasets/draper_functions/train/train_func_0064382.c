s5p_mfc_watchdog(unsigned long arg)
{
	struct s5p_mfc_dev *dev = (struct s5p_mfc_dev *)arg;

	if (test_bit(0, &dev->hw_lock))
		atomic_inc(&dev->watchdog_cnt);
	if (atomic_read(&dev->watchdog_cnt) >= MFC_WATCHDOG_CNT) {


		mfc_err("Time out during waiting for HW\n");
		queue_work(dev->watchdog_workqueue, &dev->watchdog_work);
	}
	dev->watchdog_timer.expires = jiffies +
					msecs_to_jiffies(MFC_WATCHDOG_INTERVAL);
	add_timer(&dev->watchdog_timer);
}
