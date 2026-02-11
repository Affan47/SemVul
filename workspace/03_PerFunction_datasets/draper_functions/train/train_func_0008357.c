efx_mcdi_mon_show_limit(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct efx_mcdi_mon_attribute *mon_attr =
		container_of(attr, struct efx_mcdi_mon_attribute, dev_attr);
	unsigned int value;

	value = mon_attr->limit_value;

	switch (mon_attr->hwmon_type) {
	case EFX_HWMON_TEMP:

		value *= 1000;
		break;
	case EFX_HWMON_POWER:

		value *= 1000000;
		break;
	default:

		break;
	}

	return sprintf(buf, "%u\n", value);
}
