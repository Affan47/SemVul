mthca_cmd_init(struct mthca_dev *dev)
{
	mutex_init(&dev->cmd.hcr_mutex);
	sema_init(&dev->cmd.poll_sem, 1);
	dev->cmd.flags = 0;

	dev->hcr = ioremap(pci_resource_start(dev->pdev, 0) + MTHCA_HCR_BASE,
			   MTHCA_HCR_SIZE);
	if (!dev->hcr) {
		mthca_err(dev, "Couldn't map command register.");
		return -ENOMEM;
	}

	dev->cmd.pool = pci_pool_create("mthca_cmd", dev->pdev,
					MTHCA_MAILBOX_SIZE,
					MTHCA_MAILBOX_SIZE, 0);
	if (!dev->cmd.pool) {
		iounmap(dev->hcr);
		return -ENOMEM;
	}

	return 0;
}
