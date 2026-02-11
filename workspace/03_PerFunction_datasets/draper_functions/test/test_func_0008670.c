atombios_get_encoder_mode(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct drm_connector *connector;
	struct radeon_connector *radeon_connector;
	struct radeon_connector_atom_dig *dig_connector;
	struct radeon_encoder_atom_dig *dig_enc;

	if (radeon_encoder_is_digital(encoder)) {
		dig_enc = radeon_encoder->enc_priv;
		if (dig_enc->active_mst_links)
			return ATOM_ENCODER_MODE_DP_MST;
	}
	if (radeon_encoder->is_mst_encoder || radeon_encoder->offset)
		return ATOM_ENCODER_MODE_DP_MST;

	if (radeon_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE)
		return ATOM_ENCODER_MODE_DP;


	if ((radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DVO1) ||
	    (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1))
		return ATOM_ENCODER_MODE_DVO;

	connector = radeon_get_connector_for_encoder(encoder);


	if (!connector)
		connector = radeon_get_connector_for_encoder_init(encoder);
	radeon_connector = to_radeon_connector(connector);

	switch (connector->connector_type) {
	case DRM_MODE_CONNECTOR_DVII:
	case DRM_MODE_CONNECTOR_HDMIB:
		if (radeon_audio != 0) {
			if (radeon_connector->use_digital &&
			    (radeon_connector->audio == RADEON_AUDIO_ENABLE))
				return ATOM_ENCODER_MODE_HDMI;
			else if (drm_detect_hdmi_monitor(radeon_connector_edid(connector)) &&
				 (radeon_connector->audio == RADEON_AUDIO_AUTO))
				return ATOM_ENCODER_MODE_HDMI;
			else if (radeon_connector->use_digital)
				return ATOM_ENCODER_MODE_DVI;
			else
				return ATOM_ENCODER_MODE_CRT;
		} else if (radeon_connector->use_digital) {
			return ATOM_ENCODER_MODE_DVI;
		} else {
			return ATOM_ENCODER_MODE_CRT;
		}
		break;
	case DRM_MODE_CONNECTOR_DVID:
	case DRM_MODE_CONNECTOR_HDMIA:
	default:
		if (radeon_audio != 0) {
			if (radeon_connector->audio == RADEON_AUDIO_ENABLE)
				return ATOM_ENCODER_MODE_HDMI;
			else if (drm_detect_hdmi_monitor(radeon_connector_edid(connector)) &&
				 (radeon_connector->audio == RADEON_AUDIO_AUTO))
				return ATOM_ENCODER_MODE_HDMI;
			else
				return ATOM_ENCODER_MODE_DVI;
		} else {
			return ATOM_ENCODER_MODE_DVI;
		}
		break;
	case DRM_MODE_CONNECTOR_LVDS:
		return ATOM_ENCODER_MODE_LVDS;
		break;
	case DRM_MODE_CONNECTOR_DisplayPort:
		dig_connector = radeon_connector->con_priv;
		if ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP)) {
			if (radeon_audio != 0 &&
			    drm_detect_monitor_audio(radeon_connector_edid(connector)) &&
			    ASIC_IS_DCE4(rdev) && !ASIC_IS_DCE5(rdev))
				return ATOM_ENCODER_MODE_DP_AUDIO;
			return ATOM_ENCODER_MODE_DP;
		} else if (radeon_audio != 0) {
			if (radeon_connector->audio == RADEON_AUDIO_ENABLE)
				return ATOM_ENCODER_MODE_HDMI;
			else if (drm_detect_hdmi_monitor(radeon_connector_edid(connector)) &&
				 (radeon_connector->audio == RADEON_AUDIO_AUTO))
				return ATOM_ENCODER_MODE_HDMI;
			else
				return ATOM_ENCODER_MODE_DVI;
		} else {
			return ATOM_ENCODER_MODE_DVI;
		}
		break;
	case DRM_MODE_CONNECTOR_eDP:
		if (radeon_audio != 0 &&
		    drm_detect_monitor_audio(radeon_connector_edid(connector)) &&
		    ASIC_IS_DCE4(rdev) && !ASIC_IS_DCE5(rdev))
			return ATOM_ENCODER_MODE_DP_AUDIO;
		return ATOM_ENCODER_MODE_DP;
	case DRM_MODE_CONNECTOR_DVIA:
	case DRM_MODE_CONNECTOR_VGA:
		return ATOM_ENCODER_MODE_CRT;
		break;
	case DRM_MODE_CONNECTOR_Composite:
	case DRM_MODE_CONNECTOR_SVIDEO:
	case DRM_MODE_CONNECTOR_9PinDIN:

		return ATOM_ENCODER_MODE_TV;

		break;
	}
}
