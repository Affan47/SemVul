dce_v8_0_program_fmt(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
	struct drm_connector *connector = amdgpu_get_connector_for_encoder(encoder);
	int bpc = 0;
	u32 tmp = 0;
	enum amdgpu_connector_dither dither = AMDGPU_FMT_DITHER_DISABLE;

	if (connector) {
		struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
		bpc = amdgpu_connector_get_monitor_bpc(connector);
		dither = amdgpu_connector->dither;
	}


	if (amdgpu_encoder->devices & ATOM_DEVICE_LCD_SUPPORT)
		return;


	if ((amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1) ||
	    (amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2))
		return;

	if (bpc == 0)
		return;

	switch (bpc) {
	case 6:
		if (dither == AMDGPU_FMT_DITHER_ENABLE)

			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_FRAME_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_HIGHPASS_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_EN_MASK |
				(0 << FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_DEPTH__SHIFT));
		else
			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_EN_MASK |
			(0 << FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_DEPTH__SHIFT));
		break;
	case 8:
		if (dither == AMDGPU_FMT_DITHER_ENABLE)

			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_FRAME_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_HIGHPASS_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_RGB_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_EN_MASK |
				(1 << FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_DEPTH__SHIFT));
		else
			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_EN_MASK |
			(1 << FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_DEPTH__SHIFT));
		break;
	case 10:
		if (dither == AMDGPU_FMT_DITHER_ENABLE)

			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_FRAME_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_HIGHPASS_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_RGB_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_EN_MASK |
				(2 << FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_DEPTH__SHIFT));
		else
			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_EN_MASK |
			(2 << FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_DEPTH__SHIFT));
		break;
	default:

		break;
	}

	WREG32(mmFMT_BIT_DEPTH_CONTROL + amdgpu_crtc->crtc_offset, tmp);
}
