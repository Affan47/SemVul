intel_mbm_init(void)
{
	int ret = 0, array_size, maxid = cqm_max_rmid + 1;

	mbm_socket_max = topology_max_packages();
	array_size = sizeof(struct sample) * maxid * mbm_socket_max;
	mbm_local = kmalloc(array_size, GFP_KERNEL);
	if (!mbm_local)
		return -ENOMEM;

	mbm_total = kmalloc(array_size, GFP_KERNEL);
	if (!mbm_total) {
		ret = -ENOMEM;
		goto out;
	}

	array_size = sizeof(struct hrtimer) * mbm_socket_max;
	mbm_timers = kmalloc(array_size, GFP_KERNEL);
	if (!mbm_timers) {
		ret = -ENOMEM;
		goto out;
	}
	mbm_hrtimer_init();

out:
	if (ret)
		mbm_cleanup();

	return ret;
}
