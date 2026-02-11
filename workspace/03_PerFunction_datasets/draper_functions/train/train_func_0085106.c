pci_notify(struct notifier_block *nb, unsigned long action,
		      void *data)
{
	struct device *dev = data;
	struct pci_dev *pdev = to_pci_dev(dev);
	bool notify = false;

	pr_debug("%s\n", __func__);


	if (action == BUS_NOTIFY_ADD_DEVICE)
		notify = vga_arbiter_add_pci_device(pdev);
	else if (action == BUS_NOTIFY_DEL_DEVICE)
		notify = vga_arbiter_del_pci_device(pdev);

	if (notify)
		vga_arbiter_notify_clients();
	return 0;
}
