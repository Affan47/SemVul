radeon_do_pixcache_flush(drm_radeon_private_t * dev_priv)
{
	u32 tmp;
	int i;

	dev_priv->stats.boxes |= RADEON_BOX_WAIT_IDLE;

	if ((dev_priv->flags & RADEON_FAMILY_MASK) <= CHIP_RV280) {
		tmp = RADEON_READ(RADEON_RB3D_DSTCACHE_CTLSTAT);
		tmp |= RADEON_RB3D_DC_FLUSH_ALL;
		RADEON_WRITE(RADEON_RB3D_DSTCACHE_CTLSTAT, tmp);

		for (i = 0; i < dev_priv->usec_timeout; i++) {
			if (!(RADEON_READ(RADEON_RB3D_DSTCACHE_CTLSTAT)
			      & RADEON_RB3D_DC_BUSY)) {
				return 0;
			}
			DRM_UDELAY(1);
		}
	} else {

		return 0;
	}

#if RADEON_FIFO_DEBUG
	DRM_ERROR("failed!\n");
	radeon_status(dev_priv);
#endif
	return -EBUSY;
}
