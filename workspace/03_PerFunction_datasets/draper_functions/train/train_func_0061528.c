edp_detect(struct intel_dp *intel_dp)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	enum drm_connector_status status;

	status = intel_panel_detect(dev);
	if (status == connector_status_unknown)
		status = connector_status_connected;

	return status;
}
