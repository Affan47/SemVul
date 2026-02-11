pci_ni8420_exit(struct pci_dev *dev)
{
	void __iomem *p;
	unsigned int bar = 0;

	if ((pci_resource_flags(dev, bar) & IORESOURCE_MEM) == 0) {
		moan_device("no memory in bar", dev);
		return;
	}

	p = pci_ioremap_bar(dev, bar);
	if (p == NULL)
		return;


	writel(readl(p + NI8420_INT_ENABLE_REG) & ~(NI8420_INT_ENABLE_BIT),
	       p + NI8420_INT_ENABLE_REG);
	iounmap(p);
}
