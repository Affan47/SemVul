netup_unidvb_ring_copy(struct netup_dma *dma,
				  struct netup_unidvb_buffer *buf)
{
	u32 copy_bytes, ring_bytes;
	u32 buff_bytes = NETUP_DMA_PACKETS_COUNT * 188 - buf->size;
	u8 *p = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	struct netup_unidvb_dev *ndev = dma->ndev;

	if (p == NULL) {
		dev_err(&ndev->pci_dev->dev,
			"%s(): buffer is NULL\n", __func__);
		return -EINVAL;
	}
	p += buf->size;
	if (dma->data_offset + dma->data_size > dma->ring_buffer_size) {
		ring_bytes = dma->ring_buffer_size - dma->data_offset;
		copy_bytes = (ring_bytes > buff_bytes) ?
			buff_bytes : ring_bytes;
		memcpy_fromio(p, (u8 __iomem *)(dma->addr_virt + dma->data_offset), copy_bytes);
		p += copy_bytes;
		buf->size += copy_bytes;
		buff_bytes -= copy_bytes;
		dma->data_size -= copy_bytes;
		dma->data_offset += copy_bytes;
		if (dma->data_offset == dma->ring_buffer_size)
			dma->data_offset = 0;
	}
	if (buff_bytes > 0) {
		ring_bytes = dma->data_size;
		copy_bytes = (ring_bytes > buff_bytes) ?
				buff_bytes : ring_bytes;
		memcpy_fromio(p, (u8 __iomem *)(dma->addr_virt + dma->data_offset), copy_bytes);
		buf->size += copy_bytes;
		dma->data_size -= copy_bytes;
		dma->data_offset += copy_bytes;
		if (dma->data_offset == dma->ring_buffer_size)
			dma->data_offset = 0;
	}
	return 0;
}
