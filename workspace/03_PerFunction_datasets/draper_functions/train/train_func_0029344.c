r300_legacy_tv_detect(struct drm_encoder *encoder,
				  struct drm_connector *connector)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	uint32_t crtc2_gen_cntl, tv_dac_cntl, dac_cntl2, dac_ext_cntl;
	uint32_t disp_output_cntl, gpiopad_a, tmp;
	bool found = false;


	gpiopad_a = RREG32(RADEON_GPIOPAD_A);
	dac_cntl2 = RREG32(RADEON_DAC_CNTL2);
	crtc2_gen_cntl = RREG32(RADEON_CRTC2_GEN_CNTL);
	dac_ext_cntl = RREG32(RADEON_DAC_EXT_CNTL);
	tv_dac_cntl = RREG32(RADEON_TV_DAC_CNTL);
	disp_output_cntl = RREG32(RADEON_DISP_OUTPUT_CNTL);

	WREG32_P(RADEON_GPIOPAD_A, 0, ~1);

	WREG32(RADEON_DAC_CNTL2, RADEON_DAC2_DAC2_CLK_SEL);

	WREG32(RADEON_CRTC2_GEN_CNTL,
	       RADEON_CRTC2_CRT2_ON | RADEON_CRTC2_VSYNC_TRISTAT);

	tmp = disp_output_cntl & ~RADEON_DISP_TVDAC_SOURCE_MASK;
	tmp |= RADEON_DISP_TVDAC_SOURCE_CRTC2;
	WREG32(RADEON_DISP_OUTPUT_CNTL, tmp);

	WREG32(RADEON_DAC_EXT_CNTL,
	       RADEON_DAC2_FORCE_BLANK_OFF_EN |
	       RADEON_DAC2_FORCE_DATA_EN |
	       RADEON_DAC_FORCE_DATA_SEL_RGB |
	       (0xec << RADEON_DAC_FORCE_DATA_SHIFT));

	WREG32(RADEON_TV_DAC_CNTL,
	       RADEON_TV_DAC_STD_NTSC |
	       (8 << RADEON_TV_DAC_BGADJ_SHIFT) |
	       (6 << RADEON_TV_DAC_DACADJ_SHIFT));

	RREG32(RADEON_TV_DAC_CNTL);
	mdelay(4);

	WREG32(RADEON_TV_DAC_CNTL,
	       RADEON_TV_DAC_NBLANK |
	       RADEON_TV_DAC_NHOLD |
	       RADEON_TV_MONITOR_DETECT_EN |
	       RADEON_TV_DAC_STD_NTSC |
	       (8 << RADEON_TV_DAC_BGADJ_SHIFT) |
	       (6 << RADEON_TV_DAC_DACADJ_SHIFT));

	RREG32(RADEON_TV_DAC_CNTL);
	mdelay(6);

	tmp = RREG32(RADEON_TV_DAC_CNTL);
	if ((tmp & RADEON_TV_DAC_GDACDET) != 0) {
		found = true;
		DRM_DEBUG_KMS("S-video TV connection detected\n");
	} else if ((tmp & RADEON_TV_DAC_BDACDET) != 0) {
		found = true;
		DRM_DEBUG_KMS("Composite TV connection detected\n");
	}

	WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);
	WREG32(RADEON_DAC_EXT_CNTL, dac_ext_cntl);
	WREG32(RADEON_CRTC2_GEN_CNTL, crtc2_gen_cntl);
	WREG32(RADEON_DISP_OUTPUT_CNTL, disp_output_cntl);
	WREG32(RADEON_DAC_CNTL2, dac_cntl2);
	WREG32_P(RADEON_GPIOPAD_A, gpiopad_a, ~1);
	return found;
}
