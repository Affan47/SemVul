check_vbus_state(struct tahvo_usb *tu)
{
	struct retu_dev *rdev = dev_get_drvdata(tu->pt_dev->dev.parent);
	int reg, prev_state;

	reg = retu_read(rdev, TAHVO_REG_IDSR);
	if (reg & TAHVO_STAT_VBUS) {
		switch (tu->phy.otg->state) {
		case OTG_STATE_B_IDLE:

			if (tu->phy.otg->gadget)
				usb_gadget_vbus_connect(tu->phy.otg->gadget);
			tu->phy.otg->state = OTG_STATE_B_PERIPHERAL;
			usb_phy_set_event(&tu->phy, USB_EVENT_ENUMERATED);
			break;
		case OTG_STATE_A_IDLE:


			tu->phy.otg->state = OTG_STATE_A_HOST;
			break;
		default:
			break;
		}
		dev_info(&tu->pt_dev->dev, "USB cable connected\n");
	} else {
		switch (tu->phy.otg->state) {
		case OTG_STATE_B_PERIPHERAL:
			if (tu->phy.otg->gadget)
				usb_gadget_vbus_disconnect(tu->phy.otg->gadget);
			tu->phy.otg->state = OTG_STATE_B_IDLE;
			usb_phy_set_event(&tu->phy, USB_EVENT_NONE);
			break;
		case OTG_STATE_A_HOST:
			tu->phy.otg->state = OTG_STATE_A_IDLE;
			break;
		default:
			break;
		}
		dev_info(&tu->pt_dev->dev, "USB cable disconnected\n");
	}

	prev_state = tu->vbus_state;
	tu->vbus_state = reg & TAHVO_STAT_VBUS;
	if (prev_state != tu->vbus_state) {
		extcon_set_cable_state_(tu->extcon, EXTCON_USB, tu->vbus_state);
		sysfs_notify(&tu->pt_dev->dev.kobj, NULL, "vbus_state");
	}
}
