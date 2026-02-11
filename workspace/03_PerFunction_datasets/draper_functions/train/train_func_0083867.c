twl4030_bci_max_current_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int status = 0;
	int cur = -1;
	u8 bcictl1;
	struct twl4030_bci *bci = dev_get_drvdata(dev->parent);

	if (dev == &bci->ac->dev) {
		if (!bci->ac_is_active)
			cur = bci->ac_cur;
	} else {
		if (bci->ac_is_active)
			cur = bci->usb_cur_target;
	}
	if (cur < 0) {
		cur = twl4030bci_read_adc_val(TWL4030_BCIIREF1);
		if (cur < 0)
			return cur;
		status = twl4030_bci_read(TWL4030_BCICTL1, &bcictl1);
		if (status < 0)
			return status;
		cur = regval2ua(cur, bcictl1 & TWL4030_CGAIN);
	}
	return scnprintf(buf, PAGE_SIZE, "%u\n", cur);
}
