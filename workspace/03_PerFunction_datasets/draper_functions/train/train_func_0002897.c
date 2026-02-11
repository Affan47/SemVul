radeon_legacy_tv_adjust_crtc_reg(struct drm_encoder *encoder,
				      uint32_t *h_total_disp, uint32_t *h_sync_strt_wid,
				      uint32_t *v_total_disp, uint32_t *v_sync_strt_wid)
{
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	const struct radeon_tv_mode_constants *const_ptr;
	uint32_t tmp;

	const_ptr = radeon_legacy_tv_get_std_mode(radeon_encoder, NULL);
	if (!const_ptr)
		return;

	*h_total_disp = (((const_ptr->hor_resolution / 8) - 1) << RADEON_CRTC_H_DISP_SHIFT) |
		(((const_ptr->hor_total / 8) - 1) << RADEON_CRTC_H_TOTAL_SHIFT);

	tmp = *h_sync_strt_wid;
	tmp &= ~(RADEON_CRTC_H_SYNC_STRT_PIX | RADEON_CRTC_H_SYNC_STRT_CHAR);
	tmp |= (((const_ptr->hor_syncstart / 8) - 1) << RADEON_CRTC_H_SYNC_STRT_CHAR_SHIFT) |
		(const_ptr->hor_syncstart & 7);
	*h_sync_strt_wid = tmp;

	*v_total_disp = ((const_ptr->ver_resolution - 1) << RADEON_CRTC_V_DISP_SHIFT) |
		((const_ptr->ver_total - 1) << RADEON_CRTC_V_TOTAL_SHIFT);

	tmp = *v_sync_strt_wid;
	tmp &= ~RADEON_CRTC_V_SYNC_STRT;
	tmp |= ((const_ptr->ver_syncstart - 1) << RADEON_CRTC_V_SYNC_STRT_SHIFT);
	*v_sync_strt_wid = tmp;
}
