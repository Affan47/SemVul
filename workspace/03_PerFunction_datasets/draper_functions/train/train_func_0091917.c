get_dma_size(struct rsxx_dma *dma)
{
	if (dma->sub_page.cnt)
		return dma->sub_page.cnt << 9;
	else
		return RSXX_HW_BLK_SIZE;
}
