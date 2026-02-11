vmw_update_seqno(struct vmw_private *dev_priv,
			 struct vmw_fifo_state *fifo_state)
{
	u32 *fifo_mem = dev_priv->mmio_virt;
	uint32_t seqno = vmw_mmio_read(fifo_mem + SVGA_FIFO_FENCE);

	if (dev_priv->last_read_seqno != seqno) {
		dev_priv->last_read_seqno = seqno;
		vmw_marker_pull(&fifo_state->marker_queue, seqno);
		vmw_fences_update(dev_priv->fman);
	}
}
