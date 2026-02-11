b44_probe(struct pci_device *pci, const struct pci_device_id *id)
{
	struct net_device *netdev;
	struct b44_private *bp;
	int rc;


	if (!phys_ram_within_limit(B44_30BIT_DMA_MASK)) {
		DBG("Sorry, this version of the driver does not\n"
		    "support systems with more than 1GB of RAM.\n");
		return -ENOMEM;
	}


	netdev = alloc_etherdev(sizeof(*bp));
	if (!netdev)
		return -ENOMEM;

	netdev_init(netdev, &b44_operations);
	pci_set_drvdata(pci, netdev);
	netdev->dev = &pci->dev;


	bp = netdev_priv(netdev);
	memset(bp, 0, sizeof(*bp));
	bp->netdev = netdev;
	bp->pci = pci;


	bp->regs = ioremap(pci->membase, B44_REGS_SIZE);
	if (!bp->regs) {
		netdev_put(netdev);
		return -ENOMEM;
	}


	adjust_pci_device(pci);

	b44_load_mac_and_phy_addr(bp);


	netdev_link_up(netdev);

	rc = register_netdev(netdev);
	if (rc != 0) {
		iounmap(bp->regs);
		netdev_put(netdev);
		return rc;
	}

	b44_chip_reset(bp, B44_CHIP_RESET_FULL);

	DBG("b44 %s (%04x:%04x) regs=%p MAC=%s\n", id->name, id->vendor,
	    id->device, bp->regs, eth_ntoa(netdev->ll_addr));

	return 0;
}
