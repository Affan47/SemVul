vmw_kms_write_svga(struct vmw_private *vmw_priv,
			unsigned width, unsigned height, unsigned pitch,
			unsigned bpp, unsigned depth)
{
	if (vmw_priv->capabilities & SVGA_CAP_PITCHLOCK)
		vmw_write(vmw_priv, SVGA_REG_PITCHLOCK, pitch);
	else if (vmw_fifo_have_pitchlock(vmw_priv))
		vmw_mmio_write(pitch, vmw_priv->mmio_virt +
			       SVGA_FIFO_PITCHLOCK);
	vmw_write(vmw_priv, SVGA_REG_WIDTH, width);
	vmw_write(vmw_priv, SVGA_REG_HEIGHT, height);
	vmw_write(vmw_priv, SVGA_REG_BITS_PER_PIXEL, bpp);

	if (vmw_read(vmw_priv, SVGA_REG_DEPTH) != depth) {
		DRM_ERROR("Invalid depth %u for %u bpp, host expects %u\n",
			  depth, bpp, vmw_read(vmw_priv, SVGA_REG_DEPTH));
		return -EINVAL;
	}

	return 0;
}
