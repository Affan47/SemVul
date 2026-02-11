i915_gem_ring_throttle(struct drm_device *dev, struct drm_file *file)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_file_private *file_priv = file->driver_priv;
	unsigned long recent_enough = jiffies - DRM_I915_THROTTLE_JIFFIES;
	struct drm_i915_gem_request *request, *target = NULL;
	int ret;

	ret = i915_gem_wait_for_error(&dev_priv->gpu_error);
	if (ret)
		return ret;


	if (i915_terminally_wedged(&dev_priv->gpu_error))
		return -EIO;

	spin_lock(&file_priv->mm.lock);
	list_for_each_entry(request, &file_priv->mm.request_list, client_list) {
		if (time_after_eq(request->emitted_jiffies, recent_enough))
			break;


		if (!request->emitted_jiffies)
			continue;

		target = request;
	}
	if (target)
		i915_gem_request_reference(target);
	spin_unlock(&file_priv->mm.lock);

	if (target == NULL)
		return 0;

	ret = __i915_wait_request(target, true, NULL, NULL);
	if (ret == 0)
		queue_delayed_work(dev_priv->wq, &dev_priv->mm.retire_work, 0);

	i915_gem_request_unreference__unlocked(target);

	return ret;
}
