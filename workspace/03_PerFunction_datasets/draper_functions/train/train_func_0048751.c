drm_getmagic(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	struct drm_auth *auth = data;
	int ret = 0;

	mutex_lock(&dev->struct_mutex);
	if (!file_priv->magic) {
		ret = idr_alloc(&file_priv->master->magic_map, file_priv,
				1, 0, GFP_KERNEL);
		if (ret >= 0)
			file_priv->magic = ret;
	}
	auth->magic = file_priv->magic;
	mutex_unlock(&dev->struct_mutex);

	DRM_DEBUG("%u\n", auth->magic);

	return ret < 0 ? ret : 0;
}
