r128_do_pixcache_flush(drm_r128_private_t *dev_priv)
{
	u32 tmp;
	int i;

	tmp = R128_READ(R128_PC_NGUI_CTLSTAT) | R128_PC_FLUSH_ALL;
	R128_WRITE(R128_PC_NGUI_CTLSTAT, tmp);

	for (i = 0; i < dev_priv->usec_timeout; i++) {
		if (!(R128_READ(R128_PC_NGUI_CTLSTAT) & R128_PC_BUSY))
			return 0;
		DRM_UDELAY(1);
	}

#if R128_FIFO_DEBUG
	DRM_ERROR("failed!\n");
#endif
	return -EBUSY;
}
