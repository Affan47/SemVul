dma_buf_unmap_attachment(struct dma_buf_attachment *attach,
				struct sg_table *sg_table,
				enum dma_data_direction direction)
{
	might_sleep();

	if (WARN_ON(!attach || !attach->dmabuf || !sg_table))
		return;

	attach->dmabuf->ops->unmap_dma_buf(attach, sg_table,
						direction);
}
