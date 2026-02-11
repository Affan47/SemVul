__cpuidle_set_driver(struct cpuidle_driver *drv)
{
	if (cpuidle_curr_driver)
		return -EBUSY;

	cpuidle_curr_driver = drv;

	return 0;
}
