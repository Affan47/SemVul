vmw_kms_restore_vga(struct vmw_private *vmw_priv)
{
	struct vmw_vga_topology_state *save;
	uint32_t i;

	vmw_write(vmw_priv, SVGA_REG_WIDTH, vmw_priv->vga_width);
	vmw_write(vmw_priv, SVGA_REG_HEIGHT, vmw_priv->vga_height);
	vmw_write(vmw_priv, SVGA_REG_BITS_PER_PIXEL, vmw_priv->vga_bpp);
	if (vmw_priv->capabilities & SVGA_CAP_PITCHLOCK)
		vmw_write(vmw_priv, SVGA_REG_PITCHLOCK,
			  vmw_priv->vga_pitchlock);
	else if (vmw_fifo_have_pitchlock(vmw_priv))
		vmw_mmio_write(vmw_priv->vga_pitchlock,
			       vmw_priv->mmio_virt + SVGA_FIFO_PITCHLOCK);

	if (!(vmw_priv->capabilities & SVGA_CAP_DISPLAY_TOPOLOGY))
		return 0;

	for (i = 0; i < vmw_priv->num_displays; ++i) {
		save = &vmw_priv->vga_save[i];
		vmw_write(vmw_priv, SVGA_REG_DISPLAY_ID, i);
		vmw_write(vmw_priv, SVGA_REG_DISPLAY_IS_PRIMARY, save->primary);
		vmw_write(vmw_priv, SVGA_REG_DISPLAY_POSITION_X, save->pos_x);
		vmw_write(vmw_priv, SVGA_REG_DISPLAY_POSITION_Y, save->pos_y);
		vmw_write(vmw_priv, SVGA_REG_DISPLAY_WIDTH, save->width);
		vmw_write(vmw_priv, SVGA_REG_DISPLAY_HEIGHT, save->height);
		vmw_write(vmw_priv, SVGA_REG_DISPLAY_ID, SVGA_ID_INVALID);
	}

	return 0;
}
