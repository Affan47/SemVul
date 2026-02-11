nv04_overlay_init(struct drm_device *device)
{
	struct nouveau_drm *drm = nouveau_drm(device);
	struct nouveau_plane *plane = kzalloc(sizeof(struct nouveau_plane), GFP_KERNEL);
	int ret;

	if (!plane)
		return;

	ret = drm_plane_init(device, &plane->base, 1 ,
			     &nv04_plane_funcs,
			     formats, 2, false);
	if (ret)
		goto err;


	plane->props.colorkey = drm_property_create_range(
			device, 0, "colorkey", 0, 0x01ffffff);
	plane->props.brightness = drm_property_create_range(
			device, 0, "brightness", 0, 1024);
	if (!plane->props.colorkey ||
	    !plane->props.brightness)
		goto cleanup;

	plane->colorkey = 0;
	drm_object_attach_property(&plane->base.base,
				   plane->props.colorkey, plane->colorkey);

	plane->brightness = 512;
	drm_object_attach_property(&plane->base.base,
				   plane->props.brightness, plane->brightness);

	nv04_disable_plane(&plane->base);
	return;
cleanup:
	drm_plane_cleanup(&plane->base);
err:
	kfree(plane);
	NV_ERROR(drm, "Failed to create plane\n");
}
