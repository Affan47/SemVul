usb_udc_attach_driver(const char *name, struct usb_gadget_driver *driver)
{
	struct usb_udc *udc = NULL;
	int ret = -ENODEV;

	mutex_lock(&udc_lock);
	list_for_each_entry(udc, &udc_list, list) {
		ret = strcmp(name, dev_name(&udc->dev));
		if (!ret)
			break;
	}
	if (ret) {
		ret = -ENODEV;
		goto out;
	}
	if (udc->driver) {
		ret = -EBUSY;
		goto out;
	}
	ret = udc_bind_to_driver(udc, driver);
out:
	mutex_unlock(&udc_lock);
	return ret;
}
