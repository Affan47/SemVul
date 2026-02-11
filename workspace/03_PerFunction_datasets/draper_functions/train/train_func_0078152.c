vb2_dma_sg_get_dmabuf(void *buf_priv, unsigned long flags)
{
	struct vb2_dma_sg_buf *buf = buf_priv;
	struct dma_buf *dbuf;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &vb2_dma_sg_dmabuf_ops;
	exp_info.size = buf->size;
	exp_info.flags = flags;
	exp_info.priv = buf;

	if (WARN_ON(!buf->dma_sgt))
		return NULL;

	dbuf = dma_buf_export(&exp_info);
	if (IS_ERR(dbuf))
		return NULL;


	atomic_inc(&buf->refcount);

	return dbuf;
}
