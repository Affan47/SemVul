RS600_READ_MCIND(drm_radeon_private_t *dev_priv, int addr)
{
	u32 ret;
	RADEON_WRITE(RS600_MC_INDEX, ((addr & RS600_MC_ADDR_MASK) |
				      RS600_MC_IND_CITF_ARB0));
	ret = RADEON_READ(RS600_MC_DATA);
	return ret;
}
