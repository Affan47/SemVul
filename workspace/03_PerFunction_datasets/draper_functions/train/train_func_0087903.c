virtio_gpu_framebuffer_init(struct drm_device *dev,
			    struct virtio_gpu_framebuffer *vgfb,
			    struct drm_mode_fb_cmd2 *mode_cmd,
			    struct drm_gem_object *obj)
{
	int ret;
	struct virtio_gpu_object *bo;
	vgfb->obj = obj;

	bo = gem_to_virtio_gpu_obj(obj);

	ret = drm_framebuffer_init(dev, &vgfb->base, &virtio_gpu_fb_funcs);
	if (ret) {
		vgfb->obj = NULL;
		return ret;
	}
	drm_helper_mode_fill_fb_struct(&vgfb->base, mode_cmd);

	spin_lock_init(&vgfb->dirty_lock);
	vgfb->x1 = vgfb->y1 = INT_MAX;
	vgfb->x2 = vgfb->y2 = 0;
	return 0;
}
