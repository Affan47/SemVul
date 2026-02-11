lxfb_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct fb_info *info = pci_get_drvdata(pdev);

	if (state.event == PM_EVENT_SUSPEND) {
		console_lock();
		lx_powerdown(info);
		fb_set_suspend(info, 1);
		console_unlock();
	}


	return 0;
}
