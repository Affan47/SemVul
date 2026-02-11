fp_exit(void)
{
	fp_dbg("");

	if (opened_devices) {
		GSList *copy = g_slist_copy(opened_devices);
		GSList *elem = copy;
		fp_dbg("naughty app left devices open on exit!");

		do
			fp_dev_close((struct fp_dev *) elem->data);
		while ((elem = g_slist_next(elem)));

		g_slist_free(copy);
		g_slist_free(opened_devices);
		opened_devices = NULL;
	}

	fpi_data_exit();
	fpi_poll_exit();
	g_slist_free(registered_drivers);
	registered_drivers = NULL;
	libusb_exit(fpi_usb_ctx);
}
