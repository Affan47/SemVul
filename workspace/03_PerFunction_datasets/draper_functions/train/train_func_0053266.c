atombios_crtc_prepare_pll(struct drm_crtc *crtc, struct drm_display_mode *mode)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder =
		to_radeon_encoder(radeon_crtc->encoder);
	int encoder_mode = atombios_get_encoder_mode(radeon_crtc->encoder);

	radeon_crtc->bpc = 8;
	radeon_crtc->ss_enabled = false;

	if (radeon_encoder->is_mst_encoder) {
		radeon_dp_mst_prepare_pll(crtc, mode);
	} else if ((radeon_encoder->active_device & (ATOM_DEVICE_LCD_SUPPORT | ATOM_DEVICE_DFP_SUPPORT)) ||
	    (radeon_encoder_get_dp_bridge_encoder_id(radeon_crtc->encoder) != ENCODER_OBJECT_ID_NONE)) {
		struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
		struct drm_connector *connector =
			radeon_get_connector_for_encoder(radeon_crtc->encoder);
		struct radeon_connector *radeon_connector =
			to_radeon_connector(connector);
		struct radeon_connector_atom_dig *dig_connector =
			radeon_connector->con_priv;
		int dp_clock;


		radeon_connector->pixelclock_for_modeset = mode->clock;
		radeon_crtc->bpc = radeon_get_monitor_bpc(connector);

		switch (encoder_mode) {
		case ATOM_ENCODER_MODE_DP_MST:
		case ATOM_ENCODER_MODE_DP:

			dp_clock = dig_connector->dp_clock / 10;
			if (ASIC_IS_DCE4(rdev))
				radeon_crtc->ss_enabled =
					radeon_atombios_get_asic_ss_info(rdev, &radeon_crtc->ss,
									 ASIC_INTERNAL_SS_ON_DP,
									 dp_clock);
			else {
				if (dp_clock == 16200) {
					radeon_crtc->ss_enabled =
						radeon_atombios_get_ppll_ss_info(rdev,
										 &radeon_crtc->ss,
										 ATOM_DP_SS_ID2);
					if (!radeon_crtc->ss_enabled)
						radeon_crtc->ss_enabled =
							radeon_atombios_get_ppll_ss_info(rdev,
											 &radeon_crtc->ss,
											 ATOM_DP_SS_ID1);
				} else {
					radeon_crtc->ss_enabled =
						radeon_atombios_get_ppll_ss_info(rdev,
										 &radeon_crtc->ss,
										 ATOM_DP_SS_ID1);
				}

				radeon_crtc->ss_enabled = false;
			}
			break;
		case ATOM_ENCODER_MODE_LVDS:
			if (ASIC_IS_DCE4(rdev))
				radeon_crtc->ss_enabled =
					radeon_atombios_get_asic_ss_info(rdev,
									 &radeon_crtc->ss,
									 dig->lcd_ss_id,
									 mode->clock / 10);
			else
				radeon_crtc->ss_enabled =
					radeon_atombios_get_ppll_ss_info(rdev,
									 &radeon_crtc->ss,
									 dig->lcd_ss_id);
			break;
		case ATOM_ENCODER_MODE_DVI:
			if (ASIC_IS_DCE4(rdev))
				radeon_crtc->ss_enabled =
					radeon_atombios_get_asic_ss_info(rdev,
									 &radeon_crtc->ss,
									 ASIC_INTERNAL_SS_ON_TMDS,
									 mode->clock / 10);
			break;
		case ATOM_ENCODER_MODE_HDMI:
			if (ASIC_IS_DCE4(rdev))
				radeon_crtc->ss_enabled =
					radeon_atombios_get_asic_ss_info(rdev,
									 &radeon_crtc->ss,
									 ASIC_INTERNAL_SS_ON_HDMI,
									 mode->clock / 10);
			break;
		default:
			break;
		}
	}


	radeon_crtc->adjusted_clock = atombios_adjust_pll(crtc, mode);

	return true;
}
