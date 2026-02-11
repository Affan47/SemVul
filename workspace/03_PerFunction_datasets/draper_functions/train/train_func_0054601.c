vb2_vmalloc_attach_dmabuf(void *alloc_ctx, struct dma_buf *dbuf,
	unsigned long size, enum dma_data_direction dma_dir)
{
	struct vb2_vmalloc_buf *buf;

	if (dbuf->size < size)
		return ERR_PTR(-EFAULT);

	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return ERR_PTR(-ENOMEM);

	buf->dbuf = dbuf;
	buf->dma_dir = dma_dir;
	buf->size = size;

	return buf;
}
