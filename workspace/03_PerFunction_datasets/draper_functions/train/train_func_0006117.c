il3945_dump_error_log(struct device *d, struct device_attribute *attr,
		      const char *buf, size_t count)
{
	struct il_priv *il = dev_get_drvdata(d);
	char *p = (char *)buf;

	if (p[0] == '1')
		il3945_dump_nic_error_log(il);

	return strnlen(buf, count);
}
