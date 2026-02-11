state_store(struct kobject *kobj, struct kobj_attribute *attr,
			   const char *buf, size_t n)
{
	suspend_state_t state;
	int error;

	error = pm_autosleep_lock();
	if (error)
		return error;

	if (pm_autosleep_state() > PM_SUSPEND_ON) {
		error = -EBUSY;
		goto out;
	}

	state = decode_state(buf, n);
	if (state < PM_SUSPEND_MAX)
		error = pm_suspend(state);
	else if (state == PM_SUSPEND_MAX)
		error = hibernate();
	else
		error = -EINVAL;

 out:
	pm_autosleep_unlock();
	return error ? error : n;
}
