drm_vblank_on(struct drm_device *dev, unsigned int pipe)
{
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	unsigned long irqflags;

	if (WARN_ON(pipe >= dev->num_crtcs))
		return;

	spin_lock_irqsave(&dev->vbl_lock, irqflags);
	DRM_DEBUG_VBL("crtc %d, vblank enabled %d, inmodeset %d\n",
		      pipe, vblank->enabled, vblank->inmodeset);


	if (vblank->inmodeset) {
		atomic_dec(&vblank->refcount);
		vblank->inmodeset = 0;
	}

	drm_reset_vblank_timestamp(dev, pipe);


	if (atomic_read(&vblank->refcount) != 0 || drm_vblank_offdelay == 0)
		WARN_ON(drm_vblank_enable(dev, pipe));
	spin_unlock_irqrestore(&dev->vbl_lock, irqflags);
}
