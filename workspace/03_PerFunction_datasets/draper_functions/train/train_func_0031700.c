dwc3_suspend(struct device *dev)
{
	struct dwc3	*dwc = dev_get_drvdata(dev);
	unsigned long	flags;

	spin_lock_irqsave(&dwc->lock, flags);

	switch (dwc->dr_mode) {
	case USB_DR_MODE_PERIPHERAL:
	case USB_DR_MODE_OTG:
		dwc3_gadget_suspend(dwc);

	case USB_DR_MODE_HOST:
	default:
		dwc3_event_buffers_cleanup(dwc);
		break;
	}

	dwc->gctl = dwc3_readl(dwc->regs, DWC3_GCTL);
	spin_unlock_irqrestore(&dwc->lock, flags);

	usb_phy_shutdown(dwc->usb3_phy);
	usb_phy_shutdown(dwc->usb2_phy);
	phy_exit(dwc->usb2_generic_phy);
	phy_exit(dwc->usb3_generic_phy);

	pinctrl_pm_select_sleep_state(dev);

	return 0;
}
