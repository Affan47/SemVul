i740fb_suspend(struct pci_dev *dev, pm_message_t state)
{
	struct fb_info *info = pci_get_drvdata(dev);
	struct i740fb_par *par = info->par;


	if (state.event == PM_EVENT_FREEZE || state.event == PM_EVENT_PRETHAW)
		return 0;

	console_lock();
	mutex_lock(&(par->open_lock));


	if (par->ref_count == 0) {
		mutex_unlock(&(par->open_lock));
		console_unlock();
		return 0;
	}

	fb_set_suspend(info, 1);

	pci_save_state(dev);
	pci_disable_device(dev);
	pci_set_power_state(dev, pci_choose_state(dev, state));

	mutex_unlock(&(par->open_lock));
	console_unlock();

	return 0;
}
