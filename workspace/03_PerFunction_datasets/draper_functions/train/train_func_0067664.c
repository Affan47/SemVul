bcma_core_dma_translation(struct bcma_device *core)
{
	switch (core->bus->hosttype) {
	case BCMA_HOSTTYPE_SOC:
		return 0;
	case BCMA_HOSTTYPE_PCI:
		if (bcma_aread32(core, BCMA_IOST) & BCMA_IOST_DMA64)
			return BCMA_DMA_TRANSLATION_DMA64_CMT;
		else
			return BCMA_DMA_TRANSLATION_DMA32_CMT;
	default:
		bcma_err(core->bus, "DMA translation unknown for host %d\n",
			 core->bus->hosttype);
	}
	return BCMA_DMA_TRANSLATION_NONE;
}
