update_cpumask(struct cpuset *cs, struct cpuset *trialcs,
			  const char *buf)
{
	int retval;


	if (cs == &top_cpuset)
		return -EACCES;


	if (!*buf) {
		cpumask_clear(trialcs->cpus_allowed);
	} else {
		retval = cpulist_parse(buf, trialcs->cpus_allowed);
		if (retval < 0)
			return retval;

		if (!cpumask_subset(trialcs->cpus_allowed,
				    top_cpuset.cpus_allowed))
			return -EINVAL;
	}


	if (cpumask_equal(cs->cpus_allowed, trialcs->cpus_allowed))
		return 0;

	retval = validate_change(cs, trialcs);
	if (retval < 0)
		return retval;

	spin_lock_irq(&callback_lock);
	cpumask_copy(cs->cpus_allowed, trialcs->cpus_allowed);
	spin_unlock_irq(&callback_lock);


	update_cpumasks_hier(cs, trialcs->cpus_allowed);
	return 0;
}
