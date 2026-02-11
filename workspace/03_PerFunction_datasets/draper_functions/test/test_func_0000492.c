nv17_tv_set_property(struct drm_encoder *encoder,
				struct drm_connector *connector,
				struct drm_property *property,
				uint64_t val)
{
	struct drm_mode_config *conf = &encoder->dev->mode_config;
	struct drm_crtc *crtc = encoder->crtc;
	struct nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	struct nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	bool modes_changed = false;

	if (property == conf->tv_overscan_property) {
		tv_enc->overscan = val;
		if (encoder->crtc) {
			if (tv_norm->kind == CTV_ENC_MODE)
				nv17_ctv_update_rescaler(encoder);
			else
				nv17_tv_update_rescaler(encoder);
		}

	} else if (property == conf->tv_saturation_property) {
		if (tv_norm->kind != TV_ENC_MODE)
			return -EINVAL;

		tv_enc->saturation = val;
		nv17_tv_update_properties(encoder);

	} else if (property == conf->tv_hue_property) {
		if (tv_norm->kind != TV_ENC_MODE)
			return -EINVAL;

		tv_enc->hue = val;
		nv17_tv_update_properties(encoder);

	} else if (property == conf->tv_flicker_reduction_property) {
		if (tv_norm->kind != TV_ENC_MODE)
			return -EINVAL;

		tv_enc->flicker = val;
		if (encoder->crtc)
			nv17_tv_update_rescaler(encoder);

	} else if (property == conf->tv_mode_property) {
		if (connector->dpms != DRM_MODE_DPMS_OFF)
			return -EINVAL;

		tv_enc->tv_norm = val;

		modes_changed = true;

	} else if (property == conf->tv_select_subconnector_property) {
		if (tv_norm->kind != TV_ENC_MODE)
			return -EINVAL;

		tv_enc->select_subconnector = val;
		nv17_tv_update_properties(encoder);

	} else {
		return -EINVAL;
	}

	if (modes_changed) {
		drm_helper_probe_single_connector_modes(connector, 0, 0);


		if (crtc) {
			struct drm_mode_set modeset = {
				.crtc = crtc,
			};

			drm_mode_set_config_internal(&modeset);
		}
	}

	return 0;
}
