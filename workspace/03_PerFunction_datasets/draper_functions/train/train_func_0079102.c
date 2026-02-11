virtio_gpu_transfer_from_host_ioctl(struct drm_device *dev,
					       void *data,
					       struct drm_file *file)
{
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct virtio_gpu_fpriv *vfpriv = file->driver_priv;
	struct drm_virtgpu_3d_transfer_from_host *args = data;
	struct drm_gem_object *gobj = NULL;
	struct virtio_gpu_object *qobj = NULL;
	struct virtio_gpu_fence *fence;
	int ret;
	u32 offset = args->offset;
	struct virtio_gpu_box box;

	if (vgdev->has_virgl_3d == false)
		return -ENOSYS;

	gobj = drm_gem_object_lookup(dev, file, args->bo_handle);
	if (gobj == NULL)
		return -ENOENT;

	qobj = gem_to_virtio_gpu_obj(gobj);

	ret = virtio_gpu_object_reserve(qobj, false);
	if (ret)
		goto out;

	ret = ttm_bo_validate(&qobj->tbo, &qobj->placement,
			      true, false);
	if (unlikely(ret))
		goto out_unres;

	convert_to_hw_box(&box, &args->box);
	virtio_gpu_cmd_transfer_from_host_3d
		(vgdev, qobj->hw_res_handle,
		 vfpriv->ctx_id, offset, args->level,
		 &box, &fence);
	reservation_object_add_excl_fence(qobj->tbo.resv,
					  &fence->f);

	fence_put(&fence->f);
out_unres:
	virtio_gpu_object_unreserve(qobj);
out:
	drm_gem_object_unreference_unlocked(gobj);
	return ret;
}
