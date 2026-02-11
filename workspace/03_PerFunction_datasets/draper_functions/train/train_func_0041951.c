find_vfs(const struct pci_dev *pdev)
{
	struct pcistub_device *psdev = NULL;
	unsigned long flags;
	bool found = false;

	spin_lock_irqsave(&pcistub_devices_lock, flags);
	list_for_each_entry(psdev, &pcistub_devices, dev_list) {
		if (!psdev->pdev && psdev->dev != pdev
		    && pci_physfn(psdev->dev) == pdev) {
			found = true;
			break;
		}
	}
	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	if (found)
		return psdev;
	return NULL;
}
