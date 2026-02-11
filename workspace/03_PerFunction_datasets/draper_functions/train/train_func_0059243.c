nouveau_bo_name_get(struct nouveau_bo *bo, uint32_t *name)
{
	struct drm_gem_flink req = { .handle = bo->handle };
	struct nouveau_bo_priv *nvbo = nouveau_bo(bo);

	*name = nvbo->name;
	if (!*name || *name == ~0U) {
		int ret = drmIoctl(bo->device->fd, DRM_IOCTL_GEM_FLINK, &req);
		if (ret) {
			*name = 0;
			return ret;
		}
		nvbo->name = *name = req.name;
	}
	return 0;
}
