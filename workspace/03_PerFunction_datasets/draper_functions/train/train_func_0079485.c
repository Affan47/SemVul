brcmf_usb_bus_setup(struct brcmf_usbdev_info *devinfo)
{
	int ret;


	ret = brcmf_attach(devinfo->dev);
	if (ret) {
		brcmf_err("brcmf_attach failed\n");
		return ret;
	}

	ret = brcmf_usb_up(devinfo->dev);
	if (ret)
		goto fail;

	ret = brcmf_bus_start(devinfo->dev);
	if (ret)
		goto fail;

	return 0;
fail:
	brcmf_detach(devinfo->dev);
	return ret;
}
