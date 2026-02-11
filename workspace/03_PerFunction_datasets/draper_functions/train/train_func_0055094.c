write_regs_cb(struct libusb_transfer *transfer)
{
	struct write_regs_data *wrdata = transfer->user_data;
	struct libusb_control_setup *setup =
		libusb_control_transfer_get_setup(transfer);
	int r = 0;

	if (transfer->status != LIBUSB_TRANSFER_COMPLETED)
		r = -EIO;
	else if (transfer->actual_length != setup->wLength)
		r = -EPROTO;

	g_free(transfer->buffer);
	libusb_free_transfer(transfer);
	wrdata->callback(wrdata->dev, r, wrdata->user_data);
	g_free(wrdata);
}
