mga_crtc_load_lut(struct drm_crtc *crtc)
{
	struct mga_crtc *mga_crtc = to_mga_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct mga_device *mdev = dev->dev_private;
	struct drm_framebuffer *fb = crtc->primary->fb;
	int i;

	if (!crtc->enabled)
		return;

	WREG8(DAC_INDEX + MGA1064_INDEX, 0);

	if (fb && fb->bits_per_pixel == 16) {
		int inc = (fb->depth == 15) ? 8 : 4;
		u8 r, b;
		for (i = 0; i < MGAG200_LUT_SIZE; i += inc) {
			if (fb->depth == 16) {
				if (i > (MGAG200_LUT_SIZE >> 1)) {
					r = b = 0;
				} else {
					r = mga_crtc->lut_r[i << 1];
					b = mga_crtc->lut_b[i << 1];
				}
			} else {
				r = mga_crtc->lut_r[i];
				b = mga_crtc->lut_b[i];
			}

			WREG8(DAC_INDEX + MGA1064_COL_PAL, r);
			WREG8(DAC_INDEX + MGA1064_COL_PAL, mga_crtc->lut_g[i]);
			WREG8(DAC_INDEX + MGA1064_COL_PAL, b);
		}
		return;
	}
	for (i = 0; i < MGAG200_LUT_SIZE; i++) {

		WREG8(DAC_INDEX + MGA1064_COL_PAL, mga_crtc->lut_r[i]);
		WREG8(DAC_INDEX + MGA1064_COL_PAL, mga_crtc->lut_g[i]);
		WREG8(DAC_INDEX + MGA1064_COL_PAL, mga_crtc->lut_b[i]);
	}
}
