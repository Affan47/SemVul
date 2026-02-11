virtio_gpu_resource_info_ioctl(struct drm_device *dev, void *data,
					  struct drm_file *file_priv)
{
	struct drm_virtgpu_resource_info *ri = data;
	struct drm_gem_object *gobj = NULL;
	struct virtio_gpu_object *qobj = NULL;

	gobj = drm_gem_object_lookup(dev, file_priv, ri->bo_handle);
	if (gobj == NULL)
		return -ENOENT;

	qobj = gem_to_virtio_gpu_obj(gobj);

	ri->size = qobj->gem_base.size;
	ri->res_handle = qobj->hw_res_handle;
	drm_gem_object_unreference_unlocked(gobj);
	return 0;
}
