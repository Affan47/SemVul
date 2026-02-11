nv_crtc_restore(struct drm_crtc *crtc)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	int head = nv_crtc->index;
	uint8_t saved_cr21 = nv04_display(dev)->saved_reg.crtc_reg[head].CRTC[NV_CIO_CRE_21];

	if (nv_two_heads(crtc->dev))
		NVSetOwner(crtc->dev, head);

	nouveau_hw_load_state(crtc->dev, head, &nv04_display(dev)->saved_reg);
	nv_lock_vga_crtc_shadow(crtc->dev, head, saved_cr21);

	nv_crtc->last_dpms = NV_DPMS_CLEARED;
}
