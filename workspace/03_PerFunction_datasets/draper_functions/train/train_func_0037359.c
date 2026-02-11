usb_udc_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct usb_udc		*udc = container_of(dev, struct usb_udc, dev);
	int			ret;

	ret = add_uevent_var(env, "USB_UDC_NAME=%s", udc->gadget->name);
	if (ret) {
		dev_err(dev, "failed to add uevent USB_UDC_NAME\n");
		return ret;
	}

	if (udc->driver) {
		ret = add_uevent_var(env, "USB_UDC_DRIVER=%s",
				udc->driver->function);
		if (ret) {
			dev_err(dev, "failed to add uevent USB_UDC_DRIVER\n");
			return ret;
		}
	}

	return 0;
}
