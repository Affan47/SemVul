radeon_emit_irq(struct drm_device * dev)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	unsigned int ret;
	RING_LOCALS;

	atomic_inc(&dev_priv->swi_emitted);
	ret = atomic_read(&dev_priv->swi_emitted);

	BEGIN_RING(4);
	OUT_RING_REG(RADEON_LAST_SWI_REG, ret);
	OUT_RING_REG(RADEON_GEN_INT_STATUS, RADEON_SW_INT_FIRE);
	ADVANCE_RING();
	COMMIT_RING();

	return ret;
}
