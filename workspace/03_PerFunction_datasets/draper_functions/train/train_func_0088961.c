radeon_read_fb_location(drm_radeon_private_t *dev_priv)
{

	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV770)
		return RADEON_READ(R700_MC_VM_FB_LOCATION);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
		return RADEON_READ(R600_MC_VM_FB_LOCATION);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RV515)
		return R500_READ_MCIND(dev_priv, RV515_MC_FB_LOCATION);
	else if (((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS690) ||
		 ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS740))
		return RS690_READ_MCIND(dev_priv, RS690_MC_FB_LOCATION);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS600)
		return RS600_READ_MCIND(dev_priv, RS600_MC_FB_LOCATION);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) > CHIP_RV515)
		return R500_READ_MCIND(dev_priv, R520_MC_FB_LOCATION);
	else
		return RADEON_READ(RADEON_MC_FB_LOCATION);
}
