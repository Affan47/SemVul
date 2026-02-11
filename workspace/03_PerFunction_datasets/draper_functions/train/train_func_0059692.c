lio_cn68xx_set_dpi_regs(struct octeon_device *oct)
{
	u32 i;
	u32 fifo_sizes[6] = { 3, 3, 1, 1, 1, 8 };

	lio_pci_writeq(oct, CN6XXX_DPI_DMA_CTL_MASK, CN6XXX_DPI_DMA_CONTROL);
	dev_dbg(&oct->pci_dev->dev, "DPI_DMA_CONTROL: 0x%016llx\n",
		lio_pci_readq(oct, CN6XXX_DPI_DMA_CONTROL));

	for (i = 0; i < 6; i++) {


		lio_pci_writeq(oct, 0, CN6XXX_DPI_DMA_ENG_ENB(i));
		lio_pci_writeq(oct, fifo_sizes[i], CN6XXX_DPI_DMA_ENG_BUF(i));
		dev_dbg(&oct->pci_dev->dev, "DPI_ENG_BUF%d: 0x%016llx\n", i,
			lio_pci_readq(oct, CN6XXX_DPI_DMA_ENG_BUF(i)));
	}


	lio_pci_writeq(oct, 1, CN6XXX_DPI_CTL);
	dev_dbg(&oct->pci_dev->dev, "DPI_CTL: 0x%016llx\n",
		lio_pci_readq(oct, CN6XXX_DPI_CTL));
}
