tahvo_usb_set_host(struct usb_otg *otg, struct usb_bus *host)
{
	struct tahvo_usb *tu = container_of(otg->usb_phy, struct tahvo_usb,
					    phy);

	dev_dbg(&tu->pt_dev->dev, "%s %p\n", __func__, host);

	mutex_lock(&tu->serialize);

	if (host == NULL) {
		if (tu->tahvo_mode == TAHVO_MODE_HOST)
			tahvo_usb_power_off(tu);
		otg->host = NULL;
		mutex_unlock(&tu->serialize);
		return 0;
	}

	if (tu->tahvo_mode == TAHVO_MODE_HOST) {
		otg->host = NULL;
		tahvo_usb_become_host(tu);
	}

	otg->host = host;

	mutex_unlock(&tu->serialize);

	return 0;
}
