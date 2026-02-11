virtio_gpu_alloc_object(struct drm_device *dev,
						  size_t size, bool kernel,
						  bool pinned)
{
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct virtio_gpu_object *obj;
	int ret;

	ret = virtio_gpu_object_create(vgdev, size, kernel, pinned, &obj);
	if (ret)
		return ERR_PTR(ret);

	return obj;
}
