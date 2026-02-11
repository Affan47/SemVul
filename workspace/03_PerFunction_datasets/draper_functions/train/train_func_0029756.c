_dwc2_hcd_start(struct usb_hcd *hcd)
{
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	struct usb_bus *bus = hcd_to_bus(hcd);
	unsigned long flags;

	dev_dbg(hsotg->dev, "DWC OTG HCD START\n");

	spin_lock_irqsave(&hsotg->lock, flags);
	hsotg->lx_state = DWC2_L0;
	hcd->state = HC_STATE_RUNNING;
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

	if (dwc2_is_device_mode(hsotg)) {
		spin_unlock_irqrestore(&hsotg->lock, flags);
		return 0;
	}

	dwc2_hcd_reinit(hsotg);


	if (bus->root_hub) {
		dev_dbg(hsotg->dev, "DWC OTG HCD Has Root Hub\n");

		usb_hcd_resume_root_hub(hcd);
	}

	spin_unlock_irqrestore(&hsotg->lock, flags);
	return 0;
}
