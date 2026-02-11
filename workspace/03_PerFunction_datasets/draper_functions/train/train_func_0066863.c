mv5_reset_bus(struct ata_host *host, void __iomem *mmio)
{
	struct pci_dev *pdev = to_pci_dev(host->dev);
	int early_5080;

	early_5080 = (pdev->device == 0x5080) && (pdev->revision == 0);

	if (!early_5080) {
		u32 tmp = readl(mmio + MV_PCI_EXP_ROM_BAR_CTL);
		tmp |= (1 << 0);
		writel(tmp, mmio + MV_PCI_EXP_ROM_BAR_CTL);
	}

	mv_reset_pci_bus(host, mmio);
}
