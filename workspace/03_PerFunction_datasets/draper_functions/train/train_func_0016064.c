is_valid_page(struct snd_emu10k1 *emu, dma_addr_t addr)
{
	if (addr & ~emu->dma_mask) {
		dev_err(emu->card->dev,
			"max memory size is 0x%lx (addr = 0x%lx)!!\n",
			emu->dma_mask, (unsigned long)addr);
		return 0;
	}
	if (addr & (EMUPAGESIZE-1)) {
		dev_err(emu->card->dev, "page is not aligned\n");
		return 0;
	}
	return 1;
}
