vl15_watchdog_enq(struct ipath_devdata *dd)
{

	if (atomic_inc_return(&dd->ipath_sdma_vl15_count) == 1) {
		unsigned long interval = (HZ + 19) / 20;
		dd->ipath_sdma_vl15_timer.expires = jiffies + interval;
		add_timer(&dd->ipath_sdma_vl15_timer);
	}
}
