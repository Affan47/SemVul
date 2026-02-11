r600_do_cp_stop(drm_radeon_private_t *dev_priv)
{
	uint32_t cp_me;

	DRM_DEBUG("\n");

	cp_me = 0xff | R600_CP_ME_HALT;

	RADEON_WRITE(R600_CP_ME_CNTL, cp_me);

	dev_priv->cp_running = 0;
}
