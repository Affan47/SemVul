r8a66597_resume(struct device *dev)
{
	struct r8a66597		*r8a66597 = dev_get_drvdata(dev);
	struct usb_hcd		*hcd = r8a66597_to_hcd(r8a66597);

	dev_dbg(dev, "%s\n", __func__);

	enable_controller(r8a66597);
	usb_root_hub_lost_power(hcd->self.root_hub);

	return 0;
}
