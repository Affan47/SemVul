radeon_connector_hotplug(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);

	if (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) {
		struct radeon_connector_atom_dig *dig_connector =
			radeon_connector->con_priv;

		if (radeon_connector->is_mst_connector)
			return;
		if (dig_connector->is_mst) {
			radeon_dp_handle_hpd(connector);
			return;
		}
	}


	if (radeon_connector->hpd.hpd == RADEON_HPD_NONE)
		return;

	radeon_hpd_set_polarity(rdev, radeon_connector->hpd.hpd);


	if (connector->dpms != DRM_MODE_DPMS_ON)
		return;


	if (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) {
		struct radeon_connector_atom_dig *dig_connector =
			radeon_connector->con_priv;


		if (dig_connector->dp_sink_type != CONNECTOR_OBJECT_ID_DISPLAYPORT)
			return;


		dig_connector->dp_sink_type = radeon_dp_getsinktype(radeon_connector);


		if (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) {
			int saved_dpms = connector->dpms;

			if (!radeon_hpd_sense(rdev, radeon_connector->hpd.hpd)) {
				drm_helper_connector_dpms(connector, DRM_MODE_DPMS_OFF);
			} else if (radeon_dp_needs_link_train(radeon_connector)) {


				if (!radeon_dp_getdpcd(radeon_connector))
					return;


				connector->dpms = DRM_MODE_DPMS_OFF;
				drm_helper_connector_dpms(connector, DRM_MODE_DPMS_ON);
			}
			connector->dpms = saved_dpms;
		}
	}
}
