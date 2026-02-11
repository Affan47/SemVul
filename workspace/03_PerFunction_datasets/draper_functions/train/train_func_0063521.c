proc_watchdog_common(int which, struct ctl_table *table, int write,
				void __user *buffer, size_t *lenp, loff_t *ppos)
{
	int err, old, new;
	int *watchdog_param = (int *)table->data;

	get_online_cpus();
	mutex_lock(&watchdog_proc_mutex);

	if (watchdog_suspended) {

		err = -EAGAIN;
		goto out;
	}


	if (!write) {
		*watchdog_param = (watchdog_enabled & which) != 0;
		err = proc_dointvec_minmax(table, write, buffer, lenp, ppos);
	} else {
		err = proc_dointvec_minmax(table, write, buffer, lenp, ppos);
		if (err)
			goto out;


		do {
			old = watchdog_enabled;


			if (*watchdog_param)
				new = old | which;
			else
				new = old & ~which;
		} while (cmpxchg(&watchdog_enabled, old, new) != old);


		if (old == new)
			goto out;

		err = proc_watchdog_update();
	}
out:
	mutex_unlock(&watchdog_proc_mutex);
	put_online_cpus();
	return err;
}
