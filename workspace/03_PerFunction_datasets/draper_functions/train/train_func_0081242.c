xhci_calculate_lpm_timeout(struct usb_hcd *hcd,
			struct usb_device *udev, enum usb3_link_state state)
{
	struct xhci_hcd *xhci = hcd_to_xhci(hcd);
	struct usb_host_config *config;
	char *state_name;
	int i;
	u16 timeout = USB3_LPM_DISABLED;

	if (state == USB3_LPM_U1)
		state_name = "U1";
	else if (state == USB3_LPM_U2)
		state_name = "U2";
	else {
		dev_warn(&udev->dev, "Can't enable unknown link state %i\n",
				state);
		return timeout;
	}

	if (xhci_check_tier_policy(xhci, udev, state) < 0)
		return timeout;


	if (xhci_update_timeout_for_endpoint(xhci, udev, &udev->ep0.desc,
			state, &timeout))
		return timeout;

	config = udev->actconfig;
	if (!config)
		return timeout;

	for (i = 0; i < config->desc.bNumInterfaces; i++) {
		struct usb_driver *driver;
		struct usb_interface *intf = config->interface[i];

		if (!intf)
			continue;


		if (intf->dev.driver) {
			driver = to_usb_driver(intf->dev.driver);
			if (driver && driver->disable_hub_initiated_lpm) {
				dev_dbg(&udev->dev, "Hub-initiated %s disabled "
						"at request of driver %s\n",
						state_name, driver->name);
				return xhci_get_timeout_no_hub_lpm(udev, state);
			}
		}


		if (!intf->cur_altsetting)
			continue;

		if (xhci_update_timeout_for_interface(xhci, udev,
					intf->cur_altsetting,
					state, &timeout))
			return timeout;
	}
	return timeout;
}
