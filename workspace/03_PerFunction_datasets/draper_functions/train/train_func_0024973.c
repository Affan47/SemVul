hme_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct happy_meal *hp = netdev_priv(dev);

	strlcpy(info->driver, "sunhme", sizeof(info->driver));
	strlcpy(info->version, "2.02", sizeof(info->version));
	if (hp->happy_flags & HFLAG_PCI) {
		struct pci_dev *pdev = hp->happy_dev;
		strlcpy(info->bus_info, pci_name(pdev), sizeof(info->bus_info));
	}
#ifdef CONFIG_SBUS
	else {
		const struct linux_prom_registers *regs;
		struct platform_device *op = hp->happy_dev;
		regs = of_get_property(op->dev.of_node, "regs", NULL);
		if (regs)
			snprintf(info->bus_info, sizeof(info->bus_info),
				"SBUS:%d",
				regs->which_io);
	}
#endif
}
