watchdog_deferred_registration_del(struct watchdog_device *wdd)
{
	struct list_head *p, *n;
	struct watchdog_device *wdd_tmp;

	list_for_each_safe(p, n, &wtd_deferred_reg_list) {
		wdd_tmp = list_entry(p, struct watchdog_device,
				     deferred);
		if (wdd_tmp == wdd) {
			list_del(&wdd_tmp->deferred);
			break;
		}
	}
}
