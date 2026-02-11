ipc_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	resource_size_t pci_resource;
	int ret;
	int len;

	ipcdev.dev = &pci_dev_get(pdev)->dev;
	ipcdev.irq_mode = IPC_TRIGGER_MODE_IRQ;

	ret = pci_enable_device(pdev);
	if (ret)
		return ret;

	ret = pci_request_regions(pdev, "intel_pmc_ipc");
	if (ret)
		return ret;

	pci_resource = pci_resource_start(pdev, 0);
	len = pci_resource_len(pdev, 0);
	if (!pci_resource || !len) {
		dev_err(&pdev->dev, "Failed to get resource\n");
		return -ENOMEM;
	}

	init_completion(&ipcdev.cmd_complete);

	if (request_irq(pdev->irq, ioc, 0, "intel_pmc_ipc", &ipcdev)) {
		dev_err(&pdev->dev, "Failed to request irq\n");
		return -EBUSY;
	}

	ipcdev.ipc_base = ioremap_nocache(pci_resource, len);
	if (!ipcdev.ipc_base) {
		dev_err(&pdev->dev, "Failed to ioremap ipc base\n");
		free_irq(pdev->irq, &ipcdev);
		ret = -ENOMEM;
	}

	return ret;
}
