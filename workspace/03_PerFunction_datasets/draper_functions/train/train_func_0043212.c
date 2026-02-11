hp100_pci_probe(struct pci_dev *pdev,
			   const struct pci_device_id *ent)
{
	struct net_device *dev;
	int ioaddr;
	u_short pci_command;
	int err;

	if (pci_enable_device(pdev))
		return -ENODEV;

	dev = alloc_etherdev(sizeof(struct hp100_private));
	if (!dev) {
		err = -ENOMEM;
		goto out0;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);

	pci_read_config_word(pdev, PCI_COMMAND, &pci_command);
	if (!(pci_command & PCI_COMMAND_IO)) {
#ifdef HP100_DEBUG
		printk("hp100: %s: PCI I/O Bit has not been set. Setting...\n", dev->name);
#endif
		pci_command |= PCI_COMMAND_IO;
		pci_write_config_word(pdev, PCI_COMMAND, pci_command);
	}

	if (!(pci_command & PCI_COMMAND_MASTER)) {
#ifdef HP100_DEBUG
		printk("hp100: %s: PCI Master Bit has not been set. Setting...\n", dev->name);
#endif
		pci_command |= PCI_COMMAND_MASTER;
		pci_write_config_word(pdev, PCI_COMMAND, pci_command);
	}

	ioaddr = pci_resource_start(pdev, 0);
	err = hp100_probe1(dev, ioaddr, HP100_BUS_PCI, pdev);
	if (err)
		goto out1;

#ifdef HP100_DEBUG
	printk("hp100: %s: PCI adapter found at 0x%x\n", dev->name, ioaddr);
#endif
	pci_set_drvdata(pdev, dev);
	return 0;
 out1:
	free_netdev(dev);
 out0:
	pci_disable_device(pdev);
	return err;
}
