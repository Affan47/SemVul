__videobuf_to_vaddr(struct videobuf_buffer *buf)
{
	struct videobuf_dma_sg_memory *mem = buf->priv;
	BUG_ON(!mem);

	MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);

	return mem->dma.vaddr;
}
