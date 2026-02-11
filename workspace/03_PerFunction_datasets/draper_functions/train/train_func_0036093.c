sddr09_common_init(struct us_data *us) {
	int result;


	if (us->pusb_dev->actconfig->desc.bConfigurationValue != 1) {
		usb_stor_dbg(us, "active config #%d != 1 ??\n",
			     us->pusb_dev->actconfig->desc.bConfigurationValue);
		return -EINVAL;
	}

	result = usb_reset_configuration(us->pusb_dev);
	usb_stor_dbg(us, "Result of usb_reset_configuration is %d\n", result);
	if (result == -EPIPE) {
		usb_stor_dbg(us, "-- stall on control interface\n");
	} else if (result != 0) {

		usb_stor_dbg(us, "-- Unknown error.  Rejecting device\n");
		return -EINVAL;
	}

	us->extra = kzalloc(sizeof(struct sddr09_card_info), GFP_NOIO);
	if (!us->extra)
		return -ENOMEM;
	us->extra_destructor = sddr09_card_info_destructor;

	nand_init_ecc();
	return 0;
}
