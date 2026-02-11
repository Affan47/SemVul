intel_dp_destroy_mst_connector(struct drm_dp_mst_topology_mgr *mgr,
					   struct drm_connector *connector)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);
	struct drm_device *dev = connector->dev;

	intel_connector->unregister(intel_connector);


	drm_modeset_lock_all(dev);
	if (connector->state->crtc) {
		struct drm_mode_set set;
		int ret;

		memset(&set, 0, sizeof(set));
		set.crtc = connector->state->crtc,

		ret = drm_atomic_helper_set_config(&set);

		WARN(ret, "Disabling mst crtc failed with %i\n", ret);
	}

	intel_connector_remove_from_fbdev(intel_connector);
	drm_connector_cleanup(connector);
	drm_modeset_unlock_all(dev);

	kfree(intel_connector);
	DRM_DEBUG_KMS("\n");
}
