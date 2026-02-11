nv_crtc_mode_set(struct drm_crtc *crtc, struct drm_display_mode *mode,
		 struct drm_display_mode *adjusted_mode,
		 int x, int y, struct drm_framebuffer *old_fb)
{
	struct drm_device *dev = crtc->dev;
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct nouveau_drm *drm = nouveau_drm(dev);
	int ret;

	NV_DEBUG(drm, "CTRC mode on CRTC %d:\n", nv_crtc->index);
	drm_mode_debug_printmodeline(adjusted_mode);

	ret = nv_crtc_swap_fbs(crtc, old_fb);
	if (ret)
		return ret;


	nv_lock_vga_crtc_shadow(dev, nv_crtc->index, -1);

	nv_crtc_mode_set_vga(crtc, adjusted_mode);

	if (drm->device.info.family == NV_DEVICE_INFO_V0_CURIE)
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK, nv04_display(dev)->mode_reg.sel_clk);
	nv_crtc_mode_set_regs(crtc, adjusted_mode);
	nv_crtc_calc_state_ext(crtc, mode, adjusted_mode->clock);
	return 0;
}
