write_regs_iterate(struct write_regs_data *wrdata)
{
	struct libusb_control_setup *setup;
	const struct sonly_regwrite *regwrite;
	int r;

	if (wrdata->regs_written >= wrdata->num_regs) {
		write_regs_finished(wrdata, 0);
		return;
	}

	regwrite = &wrdata->regs[wrdata->regs_written];

	fp_dbg("set %02x=%02x", regwrite->reg, regwrite->value);
	setup = libusb_control_transfer_get_setup(wrdata->transfer);
	setup->wIndex = regwrite->reg;
	wrdata->transfer->buffer[LIBUSB_CONTROL_SETUP_SIZE] = regwrite->value;

	r = libusb_submit_transfer(wrdata->transfer);
	if (r < 0)
		write_regs_finished(wrdata, r);
}
