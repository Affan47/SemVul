imon_find_endpoints(struct imon_context *ictx,
				struct usb_host_interface *iface_desc)
{
	struct usb_endpoint_descriptor *ep;
	struct usb_endpoint_descriptor *rx_endpoint = NULL;
	struct usb_endpoint_descriptor *tx_endpoint = NULL;
	int ifnum = iface_desc->desc.bInterfaceNumber;
	int num_endpts = iface_desc->desc.bNumEndpoints;
	int i, ep_dir, ep_type;
	bool ir_ep_found = false;
	bool display_ep_found = false;
	bool tx_control = false;


	for (i = 0; i < num_endpts && !(ir_ep_found && display_ep_found); ++i) {
		ep = &iface_desc->endpoint[i].desc;
		ep_dir = ep->bEndpointAddress & USB_ENDPOINT_DIR_MASK;
		ep_type = usb_endpoint_type(ep);

		if (!ir_ep_found && ep_dir == USB_DIR_IN &&
		    ep_type == USB_ENDPOINT_XFER_INT) {

			rx_endpoint = ep;
			ir_ep_found = true;
			dev_dbg(ictx->dev, "%s: found IR endpoint\n", __func__);

		} else if (!display_ep_found && ep_dir == USB_DIR_OUT &&
			   ep_type == USB_ENDPOINT_XFER_INT) {
			tx_endpoint = ep;
			display_ep_found = true;
			dev_dbg(ictx->dev, "%s: found display endpoint\n", __func__);
		}
	}

	if (ifnum == 0) {
		ictx->rx_endpoint_intf0 = rx_endpoint;


		ictx->tx_endpoint = tx_endpoint;
	} else {
		ictx->rx_endpoint_intf1 = rx_endpoint;
	}


	if (!display_ep_found) {
		tx_control = true;
		display_ep_found = true;
		dev_dbg(ictx->dev, "%s: device uses control endpoint, not "
			"interface OUT endpoint\n", __func__);
	}


	if (ictx->display_type == IMON_DISPLAY_TYPE_NONE) {
		display_ep_found = false;
		dev_dbg(ictx->dev, "%s: device has no display\n", __func__);
	}


	if (ictx->display_type == IMON_DISPLAY_TYPE_VGA) {
		display_ep_found = false;
		dev_dbg(ictx->dev, "%s: iMON Touch device found\n", __func__);
	}


	if (!ir_ep_found)
		pr_err("no valid input (IR) endpoint found\n");

	ictx->tx_control = tx_control;

	if (display_ep_found)
		ictx->display_supported = true;

	return ir_ep_found;

}
