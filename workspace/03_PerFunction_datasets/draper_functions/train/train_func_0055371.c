vmw_fifo_have_pitchlock(struct vmw_private *dev_priv)
{
	u32  *fifo_mem = dev_priv->mmio_virt;
	uint32_t caps;

	if (!(dev_priv->capabilities & SVGA_CAP_EXTENDED_FIFO))
		return false;

	caps = vmw_mmio_read(fifo_mem + SVGA_FIFO_CAPABILITIES);
	if (caps & SVGA_FIFO_CAP_PITCHLOCK)
		return true;

	return false;
}
