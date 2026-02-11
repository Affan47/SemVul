target_wwn_vpd_unit_serial_store(struct config_item *item,
		const char *page, size_t count)
{
	struct t10_wwn *t10_wwn = to_t10_wwn(item);
	struct se_device *dev = t10_wwn->t10_dev;
	unsigned char buf[INQUIRY_VPD_SERIAL_LEN];


	if (dev->dev_flags & DF_FIRMWARE_VPD_UNIT_SERIAL) {
		pr_err("Underlying SCSI device firmware provided VPD"
			" Unit Serial, ignoring request\n");
		return -EOPNOTSUPP;
	}

	if (strlen(page) >= INQUIRY_VPD_SERIAL_LEN) {
		pr_err("Emulated VPD Unit Serial exceeds"
		" INQUIRY_VPD_SERIAL_LEN: %d\n", INQUIRY_VPD_SERIAL_LEN);
		return -EOVERFLOW;
	}


	if (dev->export_count) {
		pr_err("Unable to set VPD Unit Serial while"
			" active %d $FABRIC_MOD exports exist\n",
			dev->export_count);
		return -EINVAL;
	}


	memset(buf, 0, INQUIRY_VPD_SERIAL_LEN);
	snprintf(buf, INQUIRY_VPD_SERIAL_LEN, "%s", page);
	snprintf(dev->t10_wwn.unit_serial, INQUIRY_VPD_SERIAL_LEN,
			"%s", strstrip(buf));
	dev->dev_flags |= DF_EMULATED_VPD_UNIT_SERIAL;

	pr_debug("Target_Core_ConfigFS: Set emulated VPD Unit Serial:"
			" %s\n", dev->t10_wwn.unit_serial);

	return count;
}
