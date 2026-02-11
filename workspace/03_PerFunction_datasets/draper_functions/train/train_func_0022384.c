intel_plane_init(struct drm_device *dev, enum pipe pipe, int plane)
{
	struct intel_plane *intel_plane;
	struct intel_plane_state *state;
	unsigned long possible_crtcs;
	const uint32_t *plane_formats;
	int num_plane_formats;
	int ret;

	if (INTEL_INFO(dev)->gen < 5)
		return -ENODEV;

	intel_plane = kzalloc(sizeof(*intel_plane), GFP_KERNEL);
	if (!intel_plane)
		return -ENOMEM;

	state = intel_create_plane_state(&intel_plane->base);
	if (!state) {
		kfree(intel_plane);
		return -ENOMEM;
	}
	intel_plane->base.state = &state->base;

	switch (INTEL_INFO(dev)->gen) {
	case 5:
	case 6:
		intel_plane->can_scale = true;
		intel_plane->max_downscale = 16;
		intel_plane->update_plane = ilk_update_plane;
		intel_plane->disable_plane = ilk_disable_plane;

		if (IS_GEN6(dev)) {
			plane_formats = snb_plane_formats;
			num_plane_formats = ARRAY_SIZE(snb_plane_formats);
		} else {
			plane_formats = ilk_plane_formats;
			num_plane_formats = ARRAY_SIZE(ilk_plane_formats);
		}
		break;

	case 7:
	case 8:
		if (IS_IVYBRIDGE(dev)) {
			intel_plane->can_scale = true;
			intel_plane->max_downscale = 2;
		} else {
			intel_plane->can_scale = false;
			intel_plane->max_downscale = 1;
		}

		if (IS_VALLEYVIEW(dev)) {
			intel_plane->update_plane = vlv_update_plane;
			intel_plane->disable_plane = vlv_disable_plane;

			plane_formats = vlv_plane_formats;
			num_plane_formats = ARRAY_SIZE(vlv_plane_formats);
		} else {
			intel_plane->update_plane = ivb_update_plane;
			intel_plane->disable_plane = ivb_disable_plane;

			plane_formats = snb_plane_formats;
			num_plane_formats = ARRAY_SIZE(snb_plane_formats);
		}
		break;
	case 9:
		intel_plane->can_scale = true;
		intel_plane->update_plane = skl_update_plane;
		intel_plane->disable_plane = skl_disable_plane;
		state->scaler_id = -1;

		plane_formats = skl_plane_formats;
		num_plane_formats = ARRAY_SIZE(skl_plane_formats);
		break;
	default:
		kfree(intel_plane);
		return -ENODEV;
	}

	intel_plane->pipe = pipe;
	intel_plane->plane = plane;
	intel_plane->frontbuffer_bit = INTEL_FRONTBUFFER_SPRITE(pipe, plane);
	intel_plane->check_plane = intel_check_sprite_plane;
	intel_plane->commit_plane = intel_commit_sprite_plane;
	possible_crtcs = (1 << pipe);
	ret = drm_universal_plane_init(dev, &intel_plane->base, possible_crtcs,
				       &intel_plane_funcs,
				       plane_formats, num_plane_formats,
				       DRM_PLANE_TYPE_OVERLAY);
	if (ret) {
		kfree(intel_plane);
		goto out;
	}

	intel_create_rotation_property(dev, intel_plane);

	drm_plane_helper_add(&intel_plane->base, &intel_plane_helper_funcs);

out:
	return ret;
}
