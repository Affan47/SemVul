watchdog_get_status(struct watchdog_device *wdd,
							unsigned int *status)
{
	int err = 0;

	*status = 0;
	if (!wdd->ops->status)
		return -EOPNOTSUPP;

	mutex_lock(&wdd->lock);

	if (test_bit(WDOG_UNREGISTERED, &wdd->status)) {
		err = -ENODEV;
		goto out_status;
	}

	*status = wdd->ops->status(wdd);

out_status:
	mutex_unlock(&wdd->lock);
	return err;
}
