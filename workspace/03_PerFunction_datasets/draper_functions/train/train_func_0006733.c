set_postcode(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	int ret;
	u32 tmp;
	long unsigned int tmp2;

	ret = kstrtoul(buf, 10, &tmp2);
	if (ret || tmp2 != 1)
		return -EINVAL;


	tmp = (u32) tmp2;
	ret = hp_wmi_perform_query(HPWMI_POSTCODEERROR_QUERY, 1, &tmp,
				       sizeof(tmp), sizeof(tmp));
	if (ret)
		return ret < 0 ? ret : -EINVAL;

	return count;
}
