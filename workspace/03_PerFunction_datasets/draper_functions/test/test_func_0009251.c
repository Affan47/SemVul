drm_atomic_helper_connector_dpms(struct drm_connector *connector,
				     int mode)
{
	struct drm_mode_config *config = &connector->dev->mode_config;
	struct drm_atomic_state *state;
	struct drm_crtc_state *crtc_state;
	struct drm_crtc *crtc;
	struct drm_connector *tmp_connector;
	int ret;
	bool active = false;
	int old_mode = connector->dpms;

	if (mode != DRM_MODE_DPMS_ON)
		mode = DRM_MODE_DPMS_OFF;

	connector->dpms = mode;
	crtc = connector->state->crtc;

	if (!crtc)
		return 0;

	state = drm_atomic_state_alloc(connector->dev);
	if (!state)
		return -ENOMEM;

	state->acquire_ctx = drm_modeset_legacy_acquire_ctx(crtc);
retry:
	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	if (IS_ERR(crtc_state)) {
		ret = PTR_ERR(crtc_state);
		goto fail;
	}

	WARN_ON(!drm_modeset_is_locked(&config->connection_mutex));

	drm_for_each_connector(tmp_connector, connector->dev) {
		if (tmp_connector->state->crtc != crtc)
			continue;

		if (tmp_connector->dpms == DRM_MODE_DPMS_ON) {
			active = true;
			break;
		}
	}
	crtc_state->active = active;

	ret = drm_atomic_commit(state);
	if (ret != 0)
		goto fail;


	return 0;
fail:
	if (ret == -EDEADLK)
		goto backoff;

	connector->dpms = old_mode;
	drm_atomic_state_free(state);

	return ret;
backoff:
	drm_atomic_state_clear(state);
	drm_atomic_legacy_backoff(state);

	goto retry;
}
