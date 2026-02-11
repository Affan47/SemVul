hsw_trans_edp_pipe_A_crc_wa(struct drm_device *dev, bool enable)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *crtc =
		to_intel_crtc(dev_priv->pipe_to_crtc_mapping[PIPE_A]);
	struct intel_crtc_state *pipe_config;
	struct drm_atomic_state *state;
	int ret = 0;

	drm_modeset_lock_all(dev);
	state = drm_atomic_state_alloc(dev);
	if (!state) {
		ret = -ENOMEM;
		goto out;
	}

	state->acquire_ctx = drm_modeset_legacy_acquire_ctx(&crtc->base);
	pipe_config = intel_atomic_get_crtc_state(state, crtc);
	if (IS_ERR(pipe_config)) {
		ret = PTR_ERR(pipe_config);
		goto out;
	}

	pipe_config->pch_pfit.force_thru = enable;
	if (pipe_config->cpu_transcoder == TRANSCODER_EDP &&
	    pipe_config->pch_pfit.enabled != enable)
		pipe_config->base.connectors_changed = true;

	ret = drm_atomic_commit(state);
out:
	drm_modeset_unlock_all(dev);
	WARN(ret, "Toggling workaround to %i returns %i\n", enable, ret);
	if (ret)
		drm_atomic_state_free(state);
}
