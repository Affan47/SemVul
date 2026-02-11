store_selfballooning(struct device *dev,
			    struct device_attribute *attr,
			    const char *buf,
			    size_t count)
{
	bool was_enabled = xen_selfballooning_enabled;
	unsigned long tmp;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	err = kstrtoul(buf, 10, &tmp);
	if (err)
		return err;
	if ((tmp != 0) && (tmp != 1))
		return -EINVAL;

	xen_selfballooning_enabled = !!tmp;
	if (!was_enabled && xen_selfballooning_enabled)
		schedule_delayed_work(&selfballoon_worker,
			selfballoon_interval * HZ);

	return count;
}
