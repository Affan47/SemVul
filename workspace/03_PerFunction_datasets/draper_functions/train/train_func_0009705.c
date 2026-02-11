fw_iso_buffer_destroy(struct fw_iso_buffer *buffer,
			   struct fw_card *card)
{
	int i;
	dma_addr_t address;

	for (i = 0; i < buffer->page_count_mapped; i++) {
		address = page_private(buffer->pages[i]);
		dma_unmap_page(card->device, address,
			       PAGE_SIZE, buffer->direction);
	}
	for (i = 0; i < buffer->page_count; i++)
		__free_page(buffer->pages[i]);

	kfree(buffer->pages);
	buffer->pages = NULL;
	buffer->page_count = 0;
	buffer->page_count_mapped = 0;
}
