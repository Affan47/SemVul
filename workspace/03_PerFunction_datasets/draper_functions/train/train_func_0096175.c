nv40_backlight_init(struct drm_connector *connector)
{
	struct nouveau_drm *drm = nouveau_drm(connector->dev);
	struct nvif_object *device = &drm->device.object;
	struct backlight_properties props;
	struct backlight_device *bd;

	if (!(nvif_rd32(device, NV40_PMC_BACKLIGHT) & NV40_PMC_BACKLIGHT_MASK))
		return 0;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 31;
	bd = backlight_device_register("nv_backlight", connector->kdev, drm,
				       &nv40_bl_ops, &props);
	if (IS_ERR(bd))
		return PTR_ERR(bd);
	drm->backlight = bd;
	bd->props.brightness = nv40_get_intensity(bd);
	backlight_update_status(bd);

	return 0;
}
