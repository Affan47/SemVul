quirk_isa_dma_hangs(struct pci_dev *dev)
{
	if (!isa_dma_bridge_buggy) {
		isa_dma_bridge_buggy = 1;
		dev_info(&dev->dev, "Activating ISA DMA hang workarounds\n");
	}
}
