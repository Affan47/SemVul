mwl8k_send_fw_load_cmd(struct mwl8k_priv *priv, void *data, int length)
{
	void __iomem *regs = priv->regs;
	dma_addr_t dma_addr;
	int loops;

	dma_addr = pci_map_single(priv->pdev, data, length, PCI_DMA_TODEVICE);
	if (pci_dma_mapping_error(priv->pdev, dma_addr))
		return -ENOMEM;

	iowrite32(dma_addr, regs + MWL8K_HIU_GEN_PTR);
	iowrite32(0, regs + MWL8K_HIU_INT_CODE);
	iowrite32(MWL8K_H2A_INT_DOORBELL,
		regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);
	iowrite32(MWL8K_H2A_INT_DUMMY,
		regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);

	loops = 1000;
	do {
		u32 int_code;
		if (priv->is_8764) {
			int_code = ioread32(regs +
					    MWL8K_HIU_H2A_INTERRUPT_STATUS);
			if (int_code == 0)
				break;
		} else {
			int_code = ioread32(regs + MWL8K_HIU_INT_CODE);
			if (int_code == MWL8K_INT_CODE_CMD_FINISHED) {
				iowrite32(0, regs + MWL8K_HIU_INT_CODE);
				break;
			}
		}
		cond_resched();
		udelay(1);
	} while (--loops);

	pci_unmap_single(priv->pdev, dma_addr, length, PCI_DMA_TODEVICE);

	return loops ? 0 : -ETIMEDOUT;
}
