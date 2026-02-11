vc4_plane_init(struct drm_device *dev,
				 enum drm_plane_type type)
{
	struct drm_plane *plane = NULL;
	struct vc4_plane *vc4_plane;
	u32 formats[ARRAY_SIZE(hvs_formats)];
	int ret = 0;
	unsigned i;

	vc4_plane = devm_kzalloc(dev->dev, sizeof(*vc4_plane),
				 GFP_KERNEL);
	if (!vc4_plane) {
		ret = -ENOMEM;
		goto fail;
	}

	for (i = 0; i < ARRAY_SIZE(hvs_formats); i++)
		formats[i] = hvs_formats[i].drm;
	plane = &vc4_plane->base;
	ret = drm_universal_plane_init(dev, plane, 0xff,
				       &vc4_plane_funcs,
				       formats, ARRAY_SIZE(formats),
				       type);

	drm_plane_helper_add(plane, &vc4_plane_helper_funcs);

	return plane;
fail:
	if (plane)
		vc4_plane_destroy(plane);

	return ERR_PTR(ret);
}
