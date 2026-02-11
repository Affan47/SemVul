s3_pci_resume(struct pci_dev* dev)
{
	struct fb_info *info = pci_get_drvdata(dev);
	struct s3fb_info *par = info->par;
	int err;

	dev_info(info->device, "resume\n");

	console_lock();
	mutex_lock(&(par->open_lock));

	if (par->ref_count == 0) {
		mutex_unlock(&(par->open_lock));
		console_unlock();
		return 0;
	}

	pci_set_power_state(dev, PCI_D0);
	pci_restore_state(dev);
	err = pci_enable_device(dev);
	if (err) {
		mutex_unlock(&(par->open_lock));
		console_unlock();
		dev_err(info->device, "error %d enabling device for resume\n", err);
		return err;
	}
	pci_set_master(dev);

	s3fb_set_par(info);
	fb_set_suspend(info, 0);

	mutex_unlock(&(par->open_lock));
	console_unlock();

	return 0;
}
