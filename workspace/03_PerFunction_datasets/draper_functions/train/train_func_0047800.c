isp1362_resume(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	unsigned long flags;

	DBG(0, "%s: Resuming\n", __func__);

	if (pdev->dev.power.power_state.event == PM_EVENT_SUSPEND) {
		DBG(0, "%s: Resume RH ports\n", __func__);
		spin_lock_irqsave(&isp1362_hcd->lock, flags);
		isp1362_write_reg32(isp1362_hcd, HCRHSTATUS, RH_HS_LPSC);
		spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
		return 0;
	}

	pdev->dev.power.power_state = PMSG_ON;

	return isp1362_bus_resume(isp1362_hcd_to_hcd(isp1362_hcd));
}
