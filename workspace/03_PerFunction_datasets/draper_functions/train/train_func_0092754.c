nv17_ctv_update_rescaler(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	int head = nouveau_crtc(encoder->crtc)->index;
	struct nv04_crtc_reg *regs = &nv04_display(dev)->mode_reg.crtc_reg[head];
	struct drm_display_mode *crtc_mode = &encoder->crtc->mode;
	struct drm_display_mode *output_mode =
		&get_tv_norm(encoder)->ctv_enc_mode.mode;
	int overscan, hmargin, vmargin, hratio, vratio;


	if (output_mode->flags & DRM_MODE_FLAG_INTERLACE)
		overscan = 100;
	else
		overscan = tv_enc->overscan;

	hmargin = (output_mode->hdisplay - crtc_mode->hdisplay) / 2;
	vmargin = (output_mode->vdisplay - crtc_mode->vdisplay) / 2;

	hmargin = interpolate(0, min(hmargin, output_mode->hdisplay/20),
			      hmargin, overscan);
	vmargin = interpolate(0, min(vmargin, output_mode->vdisplay/20),
			      vmargin, overscan);

	hratio = crtc_mode->hdisplay * 0x800 /
		(output_mode->hdisplay - 2*hmargin);
	vratio = crtc_mode->vdisplay * 0x800 /
		(output_mode->vdisplay - 2*vmargin) & ~3;

	regs->fp_horiz_regs[FP_VALID_START] = hmargin;
	regs->fp_horiz_regs[FP_VALID_END] = output_mode->hdisplay - hmargin - 1;
	regs->fp_vert_regs[FP_VALID_START] = vmargin;
	regs->fp_vert_regs[FP_VALID_END] = output_mode->vdisplay - vmargin - 1;

	regs->fp_debug_1 = NV_PRAMDAC_FP_DEBUG_1_YSCALE_TESTMODE_ENABLE |
		XLATE(vratio, 0, NV_PRAMDAC_FP_DEBUG_1_YSCALE_VALUE) |
		NV_PRAMDAC_FP_DEBUG_1_XSCALE_TESTMODE_ENABLE |
		XLATE(hratio, 0, NV_PRAMDAC_FP_DEBUG_1_XSCALE_VALUE);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HVALID_START,
		      regs->fp_horiz_regs[FP_VALID_START]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HVALID_END,
		      regs->fp_horiz_regs[FP_VALID_END]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_VVALID_START,
		      regs->fp_vert_regs[FP_VALID_START]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_VVALID_END,
		      regs->fp_vert_regs[FP_VALID_END]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_1, regs->fp_debug_1);
}
