msm_otg_set_host(struct usb_otg *otg, struct usb_bus *host)
{
	struct msm_otg *motg = container_of(otg->usb_phy, struct msm_otg, phy);
	struct usb_hcd *hcd;


	if (motg->pdata->mode == USB_DR_MODE_PERIPHERAL) {
		dev_info(otg->usb_phy->dev, "Host mode is not supported\n");
		return -ENODEV;
	}

	if (!host) {
		if (otg->state == OTG_STATE_A_HOST) {
			pm_runtime_get_sync(otg->usb_phy->dev);
			msm_otg_start_host(otg->usb_phy, 0);
			otg->host = NULL;
			otg->state = OTG_STATE_UNDEFINED;
			schedule_work(&motg->sm_work);
		} else {
			otg->host = NULL;
		}

		return 0;
	}

	hcd = bus_to_hcd(host);
	hcd->power_budget = motg->pdata->power_budget;

	otg->host = host;
	dev_dbg(otg->usb_phy->dev, "host driver registered w/ tranceiver\n");


	if (motg->pdata->mode == USB_DR_MODE_HOST || otg->gadget) {
		pm_runtime_get_sync(otg->usb_phy->dev);
		schedule_work(&motg->sm_work);
	}

	return 0;
}
