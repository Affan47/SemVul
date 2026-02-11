vpdma_alloc_desc_buf(struct vpdma_buf *buf, size_t size)
{
	buf->size = size;
	buf->mapped = false;
	buf->addr = kzalloc(size, GFP_KERNEL);
	if (!buf->addr)
		return -ENOMEM;

	WARN_ON(((unsigned long)buf->addr & VPDMA_DESC_ALIGN) != 0);

	return 0;
}
