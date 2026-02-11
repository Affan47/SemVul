set_attr_rdpmc(struct device *cdev,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	unsigned long val;
	ssize_t ret;

	ret = kstrtoul(buf, 0, &val);
	if (ret)
		return ret;

	if (val > 2)
		return -EINVAL;

	if (x86_pmu.attr_rdpmc_broken)
		return -ENOTSUPP;

	if ((val == 2) != (x86_pmu.attr_rdpmc == 2)) {


		if (val == 2)
			static_key_slow_inc(&rdpmc_always_available);
		else
			static_key_slow_dec(&rdpmc_always_available);
		on_each_cpu(refresh_pce, NULL, 1);
	}

	x86_pmu.attr_rdpmc = val;

	return count;
}
