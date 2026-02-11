r600_do_wait_for_fifo(drm_radeon_private_t *dev_priv, int entries)
{
	int i;

	dev_priv->stats.boxes |= RADEON_BOX_WAIT_IDLE;

	for (i = 0; i < dev_priv->usec_timeout; i++) {
		int slots;
		if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV770)
			slots = (RADEON_READ(R600_GRBM_STATUS)
				 & R700_CMDFIFO_AVAIL_MASK);
		else
			slots = (RADEON_READ(R600_GRBM_STATUS)
				 & R600_CMDFIFO_AVAIL_MASK);
		if (slots >= entries)
			return 0;
		DRM_UDELAY(1);
	}
	DRM_INFO("wait for fifo failed status : 0x%08X 0x%08X\n",
		 RADEON_READ(R600_GRBM_STATUS),
		 RADEON_READ(R600_GRBM_STATUS2));

	return -EBUSY;
}
