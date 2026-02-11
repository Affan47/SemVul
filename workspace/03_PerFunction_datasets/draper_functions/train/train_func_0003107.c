toshiba_sleep_functions_status_get(struct toshiba_acpi_dev *dev,
					      u32 *mode)
{
	u32 in[TCI_WORDS] = { SCI_GET, SCI_USB_SLEEP_CHARGE, 0, 0, 0, 0 };
	u32 out[TCI_WORDS];
	acpi_status status;

	if (!sci_open(dev))
		return -EIO;

	in[5] = SCI_USB_CHARGE_BAT_LVL;
	status = tci_raw(dev, in, out);
	sci_close(dev);
	if (ACPI_FAILURE(status)) {
		pr_err("ACPI call to get USB S&C battery level failed\n");
	} else if (out[0] == TOS_NOT_SUPPORTED) {
		return -ENODEV;
	} else if (out[0] == TOS_SUCCESS) {
		*mode = out[2];
		return 0;
	}

	return -EIO;
}
