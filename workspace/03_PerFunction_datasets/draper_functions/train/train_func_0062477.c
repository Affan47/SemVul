hsu_dma_active_desc_size(struct hsu_dma_chan *hsuc)
{
	struct hsu_dma_desc *desc = hsuc->desc;
	size_t bytes = hsu_dma_desc_size(desc);
	int i;

	i = desc->active % HSU_DMA_CHAN_NR_DESC;
	do {
		bytes += hsu_chan_readl(hsuc, HSU_CH_DxTSR(i));
	} while (--i >= 0);

	return bytes;
}
