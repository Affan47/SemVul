open_scanner(KodakAio_Scanner *s)
{
	SANE_Status status = 0;

	DBG(7, "%s: %s\n", __func__, s->hw->sane.name);

	if (s->fd != -1) {
		DBG(7, "scanner is already open: fd = %d\n", s->fd);
		return SANE_STATUS_GOOD;
	}

	if (s->hw->connection == SANE_KODAKAIO_NET) {

		char IP[1024];
		unsigned int model = 0;
		if (!split_scanner_name (s->hw->sane.name, IP, &model))
			return SANE_STATUS_INVAL;
			DBG(7, "split_scanner_name OK model=0x%x\n",model);

		status = sanei_tcp_open(IP, 9101, &s->fd);

		if (status != SANE_STATUS_GOOD ) DBG(1, "Is network scanner switched on?\n");

		if (model>0)
			k_set_device (s, model);
		if (status == SANE_STATUS_GOOD) {
			status = sanei_kodakaio_net_open (s);
		}
else			DBG(7, "status was not good at 1829\n");


	} else if (s->hw->connection == SANE_KODAKAIO_USB) {
			DBG(7, "trying to open usb\n");
		status = sanei_usb_open(s->hw->sane.name, &s->fd);
		if (s->hw->cap->out_ep>0)
			sanei_usb_set_endpoint (s->fd,
				USB_DIR_OUT | USB_ENDPOINT_TYPE_BULK, s->hw->cap->out_ep);
		if (s->hw->cap->in_ep>0)
			sanei_usb_set_endpoint (s->fd,
				USB_DIR_IN | USB_ENDPOINT_TYPE_BULK, s->hw->cap->in_ep);
	}

	if (status == SANE_STATUS_ACCESS_DENIED) {
		DBG(1, "please check that you have permissions on the device.\n");
		DBG(1, "if this is a multi-function device with a printer,\n");
		DBG(1, "disable any conflicting driver (like usblp).\n");
	}

	if (status != SANE_STATUS_GOOD)
		DBG(1, "%s open failed: %s\n", s->hw->sane.name,
			sane_strstatus(status));
	else
		DBG(3, "scanner opened\n");


	return status;
}
