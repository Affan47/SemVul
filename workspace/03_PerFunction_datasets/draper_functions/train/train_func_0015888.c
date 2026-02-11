tahvo_usb_power_off(struct tahvo_usb *tu)
{
	struct retu_dev *rdev = dev_get_drvdata(tu->pt_dev->dev.parent);


	if (tu->phy.otg->gadget)
		usb_gadget_vbus_disconnect(tu->phy.otg->gadget);


	retu_write(rdev, TAHVO_REG_USBR, 0);
	tu->phy.otg->state = OTG_STATE_UNDEFINED;
}
