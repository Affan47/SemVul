bfa_flash_read_end(void __iomem *pci_bar, u32 len, char *buf)
{

	u32 i;


	for (i = 0; i < len; i += 4) {
		u32 w = readl(pci_bar + FLI_RDDATA_REG);
		*((u32 *) (buf + i)) = swab32(w);
	}

	bfa_flash_fifo_flush(pci_bar);
}
