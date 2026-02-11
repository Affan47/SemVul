twl4030_bci_mode_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct twl4030_bci *bci = dev_get_drvdata(dev->parent);
	int len = 0;
	int i;
	int mode = bci->usb_mode;

	if (dev == &bci->ac->dev)
		mode = bci->ac_mode;

	for (i = 0; i < ARRAY_SIZE(modes); i++)
		if (mode == i)
			len += snprintf(buf+len, PAGE_SIZE-len,
					"[%s] ", modes[i]);
		else
			len += snprintf(buf+len, PAGE_SIZE-len,
					"%s ", modes[i]);
	buf[len-1] = '\n';
	return len;
}
