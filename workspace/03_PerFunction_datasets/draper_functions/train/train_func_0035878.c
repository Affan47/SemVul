carl9170_usb_probe(struct usb_interface *intf,
			      const struct usb_device_id *id)
{
	struct usb_endpoint_descriptor *ep;
	struct ar9170 *ar;
	struct usb_device *udev;
	int i, err;

	err = usb_reset_device(interface_to_usbdev(intf));
	if (err)
		return err;

	ar = carl9170_alloc(sizeof(*ar));
	if (IS_ERR(ar))
		return PTR_ERR(ar);

	udev = interface_to_usbdev(intf);
	usb_get_dev(udev);
	ar->udev = udev;
	ar->intf = intf;
	ar->features = id->driver_info;


	for (i = 0; i < intf->cur_altsetting->desc.bNumEndpoints; ++i) {
		ep = &intf->cur_altsetting->endpoint[i].desc;

		if (usb_endpoint_num(ep) == AR9170_USB_EP_CMD &&
		    usb_endpoint_dir_out(ep) &&
		    usb_endpoint_type(ep) == USB_ENDPOINT_XFER_BULK)
			ar->usb_ep_cmd_is_bulk = true;
	}

	usb_set_intfdata(intf, ar);
	SET_IEEE80211_DEV(ar->hw, &intf->dev);

	init_usb_anchor(&ar->rx_anch);
	init_usb_anchor(&ar->rx_pool);
	init_usb_anchor(&ar->rx_work);
	init_usb_anchor(&ar->tx_wait);
	init_usb_anchor(&ar->tx_anch);
	init_usb_anchor(&ar->tx_cmd);
	init_usb_anchor(&ar->tx_err);
	init_completion(&ar->cmd_wait);
	init_completion(&ar->fw_boot_wait);
	init_completion(&ar->fw_load_wait);
	tasklet_init(&ar->usb_tasklet, carl9170_usb_tasklet,
		     (unsigned long)ar);

	atomic_set(&ar->tx_cmd_urbs, 0);
	atomic_set(&ar->tx_anch_urbs, 0);
	atomic_set(&ar->rx_work_urbs, 0);
	atomic_set(&ar->rx_anch_urbs, 0);
	atomic_set(&ar->rx_pool_urbs, 0);

	usb_get_dev(ar->udev);

	carl9170_set_state(ar, CARL9170_STOPPED);

	err = request_firmware_nowait(THIS_MODULE, 1, CARL9170FW_NAME,
		&ar->udev->dev, GFP_KERNEL, ar, carl9170_usb_firmware_step2);
	if (err) {
		usb_put_dev(udev);
		usb_put_dev(udev);
		carl9170_free(ar);
	}
	return err;
}
