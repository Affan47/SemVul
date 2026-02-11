radeon_dig_monitor_is_duallink(struct drm_encoder *encoder,
				    u32 pixel_clock)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct drm_connector *connector;
	struct radeon_connector *radeon_connector;
	struct radeon_connector_atom_dig *dig_connector;

	connector = radeon_get_connector_for_encoder(encoder);


	if (!connector)
		connector = radeon_get_connector_for_encoder_init(encoder);
	radeon_connector = to_radeon_connector(connector);

	switch (connector->connector_type) {
	case DRM_MODE_CONNECTOR_DVII:
	case DRM_MODE_CONNECTOR_HDMIB:
		if (radeon_connector->use_digital) {

			if (ASIC_IS_DCE6(rdev) && drm_detect_hdmi_monitor(radeon_connector_edid(connector))) {
				if (pixel_clock > 340000)
					return true;
				else
					return false;
			} else {
				if (pixel_clock > 165000)
					return true;
				else
					return false;
			}
		} else
			return false;
	case DRM_MODE_CONNECTOR_DVID:
	case DRM_MODE_CONNECTOR_HDMIA:
	case DRM_MODE_CONNECTOR_DisplayPort:
		if (radeon_connector->is_mst_connector)
			return false;

		dig_connector = radeon_connector->con_priv;
		if ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP))
			return false;
		else {

			if (ASIC_IS_DCE6(rdev) && drm_detect_hdmi_monitor(radeon_connector_edid(connector))) {
				if (pixel_clock > 340000)
					return true;
				else
					return false;
			} else {
				if (pixel_clock > 165000)
					return true;
				else
					return false;
			}
		}
	default:
		return false;
	}
}
