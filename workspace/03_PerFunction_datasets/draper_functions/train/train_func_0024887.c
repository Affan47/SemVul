savagefb_suspend(struct pci_dev *dev, pm_message_t mesg)
{
	struct fb_info *info = pci_get_drvdata(dev);
	struct savagefb_par *par = info->par;

	DBG("savagefb_suspend");

	if (mesg.event == PM_EVENT_PRETHAW)
		mesg.event = PM_EVENT_FREEZE;
	par->pm_state = mesg.event;
	dev->dev.power.power_state = mesg;


	if (mesg.event == PM_EVENT_FREEZE)
		return 0;

	console_lock();
	fb_set_suspend(info, 1);

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	savagefb_blank(FB_BLANK_POWERDOWN, info);
	savage_set_default_par(par, &par->save);
	savage_disable_mmio(par);
	pci_save_state(dev);
	pci_disable_device(dev);
	pci_set_power_state(dev, pci_choose_state(dev, mesg));
	console_unlock();

	return 0;
}
