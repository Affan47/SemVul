show_rtc(struct device *d, struct device_attribute *attr,
			char *buf)
{
	u32 len = sizeof(u32), tmp = 0;
	struct ipw_priv *p = dev_get_drvdata(d);

	if (ipw_get_ordinal(p, IPW_ORD_STAT_RTC, &tmp, &len))
		return 0;

	return sprintf(buf, "0x%08x\n", tmp);
}
