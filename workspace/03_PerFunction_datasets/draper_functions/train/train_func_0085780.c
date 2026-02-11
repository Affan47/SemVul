fw_iso_buffer_init(struct fw_iso_buffer *buffer, struct fw_card *card,
		       int page_count, enum dma_data_direction direction)
{
	int ret;

	ret = fw_iso_buffer_alloc(buffer, page_count);
	if (ret < 0)
		return ret;

	ret = fw_iso_buffer_map_dma(buffer, card, direction);
	if (ret < 0)
		fw_iso_buffer_destroy(buffer, card);

	return ret;
}
