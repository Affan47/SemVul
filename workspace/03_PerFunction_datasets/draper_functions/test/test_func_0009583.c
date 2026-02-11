virtio_gpu_surface_dirty(struct virtio_gpu_framebuffer *vgfb,
			     struct drm_clip_rect *clips,
			     unsigned num_clips)
{
	struct virtio_gpu_device *vgdev = vgfb->base.dev->dev_private;
	struct virtio_gpu_object *obj = gem_to_virtio_gpu_obj(vgfb->obj);
	struct drm_clip_rect norect;
	struct drm_clip_rect *clips_ptr;
	int left, right, top, bottom;
	int i;
	int inc = 1;
	if (!num_clips) {
		num_clips = 1;
		clips = &norect;
		norect.x1 = norect.y1 = 0;
		norect.x2 = vgfb->base.width;
		norect.y2 = vgfb->base.height;
	}
	left = clips->x1;
	right = clips->x2;
	top = clips->y1;
	bottom = clips->y2;


	for (i = 1, clips_ptr = clips + inc;
	     i < num_clips; i++, clips_ptr += inc) {
		left = min_t(int, left, (int)clips_ptr->x1);
		right = max_t(int, right, (int)clips_ptr->x2);
		top = min_t(int, top, (int)clips_ptr->y1);
		bottom = max_t(int, bottom, (int)clips_ptr->y2);
	}

	if (obj->dumb)
		return virtio_gpu_dirty_update(vgfb, false, left, top,
					       right - left, bottom - top);

	virtio_gpu_cmd_resource_flush(vgdev, obj->hw_res_handle,
				      left, top, right - left, bottom - top);
	return 0;
}
