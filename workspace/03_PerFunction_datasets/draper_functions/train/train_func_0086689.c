drm_vblank_off(struct drm_device *dev, unsigned int pipe)
{
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	struct drm_pending_vblank_event *e, *t;
	struct timeval now;
	unsigned long irqflags;
	unsigned int seq;

	if (WARN_ON(pipe >= dev->num_crtcs))
		return;

	spin_lock_irqsave(&dev->event_lock, irqflags);

	spin_lock(&dev->vbl_lock);
	DRM_DEBUG_VBL("crtc %d, vblank enabled %d, inmodeset %d\n",
		      pipe, vblank->enabled, vblank->inmodeset);


	if (drm_core_check_feature(dev, DRIVER_ATOMIC) || !vblank->inmodeset)
		vblank_disable_and_save(dev, pipe);

	wake_up(&vblank->queue);


	if (!vblank->inmodeset) {
		atomic_inc(&vblank->refcount);
		vblank->inmodeset = 1;
	}
	spin_unlock(&dev->vbl_lock);


	seq = drm_vblank_count_and_time(dev, pipe, &now);

	list_for_each_entry_safe(e, t, &dev->vblank_event_list, base.link) {
		if (e->pipe != pipe)
			continue;
		DRM_DEBUG("Sending premature vblank event on disable: "
			  "wanted %d, current %d\n",
			  e->event.sequence, seq);
		list_del(&e->base.link);
		drm_vblank_put(dev, pipe);
		send_vblank_event(dev, e, seq, &now);
	}
	spin_unlock_irqrestore(&dev->event_lock, irqflags);
}
