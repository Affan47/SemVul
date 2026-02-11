driver_probe_done(void)
{
	pr_debug("%s: probe_count = %d\n", __func__,
		 atomic_read(&probe_count));
	if (atomic_read(&probe_count))
		return -EBUSY;
	return 0;
}
