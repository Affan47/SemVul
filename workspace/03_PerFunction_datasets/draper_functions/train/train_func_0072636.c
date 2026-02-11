via_disable_vblank(struct drm_device *dev, unsigned int pipe)
{
	drm_via_private_t *dev_priv = dev->dev_private;
	u32 status;

	status = VIA_READ(VIA_REG_INTERRUPT);
	VIA_WRITE(VIA_REG_INTERRUPT, status & ~VIA_IRQ_VBLANK_ENABLE);

	VIA_WRITE8(0x83d4, 0x11);
	VIA_WRITE8(0x83d5, VIA_READ8(0x83d5) & ~0x30);

	if (pipe != 0)
		DRM_ERROR("%s:  bad crtc %u\n", __func__, pipe);
}
