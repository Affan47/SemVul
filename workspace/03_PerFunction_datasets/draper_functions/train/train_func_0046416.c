cdc_mbim_suspend(struct usb_interface *intf, pm_message_t message)
{
	int ret = -ENODEV;
	struct usbnet *dev = usb_get_intfdata(intf);
	struct cdc_mbim_state *info = (void *)&dev->data;
	struct cdc_ncm_ctx *ctx = info->ctx;

	if (!ctx)
		goto error;


	ret = usbnet_suspend(intf, message);
	if (ret < 0)
		goto error;

	if (intf == ctx->control && info->subdriver && info->subdriver->suspend)
		ret = info->subdriver->suspend(intf, message);
	if (ret < 0)
		usbnet_resume(intf);

error:
	return ret;
}
