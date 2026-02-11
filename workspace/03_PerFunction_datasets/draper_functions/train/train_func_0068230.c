intel_fbc_work_fn(struct work_struct *__work)
{
	struct drm_i915_private *dev_priv =
		container_of(__work, struct drm_i915_private, fbc.work.work);
	struct intel_fbc *fbc = &dev_priv->fbc;
	struct intel_fbc_work *work = &fbc->work;
	struct intel_crtc *crtc = fbc->crtc;
	struct drm_vblank_crtc *vblank = &dev_priv->dev->vblank[crtc->pipe];

	if (drm_crtc_vblank_get(&crtc->base)) {
		DRM_ERROR("vblank not available for FBC on pipe %c\n",
			  pipe_name(crtc->pipe));

		mutex_lock(&fbc->lock);
		work->scheduled = false;
		mutex_unlock(&fbc->lock);
		return;
	}

retry:


	wait_event_timeout(vblank->queue,
		drm_crtc_vblank_count(&crtc->base) != work->scheduled_vblank,
		msecs_to_jiffies(50));

	mutex_lock(&fbc->lock);


	if (!work->scheduled)
		goto out;


	if (drm_crtc_vblank_count(&crtc->base) == work->scheduled_vblank) {
		mutex_unlock(&fbc->lock);
		goto retry;
	}

	intel_fbc_hw_activate(dev_priv);

	work->scheduled = false;

out:
	mutex_unlock(&fbc->lock);
	drm_crtc_vblank_put(&crtc->base);
}
