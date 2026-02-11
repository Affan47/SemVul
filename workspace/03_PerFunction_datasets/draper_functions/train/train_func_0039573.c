srp_alloc_iu(struct srp_host *host, size_t size,
				   gfp_t gfp_mask,
				   enum dma_data_direction direction)
{
	struct srp_iu *iu;

	iu = kmalloc(sizeof *iu, gfp_mask);
	if (!iu)
		goto out;

	iu->buf = kzalloc(size, gfp_mask);
	if (!iu->buf)
		goto out_free_iu;

	iu->dma = ib_dma_map_single(host->srp_dev->dev, iu->buf, size,
				    direction);
	if (ib_dma_mapping_error(host->srp_dev->dev, iu->dma))
		goto out_free_buf;

	iu->size      = size;
	iu->direction = direction;

	return iu;

out_free_buf:
	kfree(iu->buf);
out_free_iu:
	kfree(iu);
out:
	return NULL;
}
