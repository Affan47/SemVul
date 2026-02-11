show_ordinals(struct device *d, struct device_attribute *attr,
			     char *buf)
{
	struct ipw2100_priv *priv = dev_get_drvdata(d);
	u32 val = 0;
	int len = 0;
	u32 val_len;
	static int loop = 0;

	if (priv->status & STATUS_RF_KILL_MASK)
		return 0;

	if (loop >= ARRAY_SIZE(ord_data))
		loop = 0;


	while (len < PAGE_SIZE - 128 && loop < ARRAY_SIZE(ord_data)) {
		val_len = sizeof(u32);

		if (ipw2100_get_ordinal(priv, ord_data[loop].index, &val,
					&val_len))
			len += sprintf(buf + len, "[0x%02X] = ERROR    %s\n",
				       ord_data[loop].index,
				       ord_data[loop].desc);
		else
			len += sprintf(buf + len, "[0x%02X] = 0x%08X %s\n",
				       ord_data[loop].index, val,
				       ord_data[loop].desc);
		loop++;
	}

	return len;
}
