i915_gem_shrinker_count(struct shrinker *shrinker, struct shrink_control *sc)
{
	struct drm_i915_private *dev_priv =
		container_of(shrinker, struct drm_i915_private, mm.shrinker);
	struct drm_device *dev = dev_priv->dev;
	struct drm_i915_gem_object *obj;
	unsigned long count;
	bool unlock;

	if (!i915_gem_shrinker_lock(dev, &unlock))
		return 0;

	count = 0;
	list_for_each_entry(obj, &dev_priv->mm.unbound_list, global_list)
		if (can_release_pages(obj))
			count += obj->base.size >> PAGE_SHIFT;

	list_for_each_entry(obj, &dev_priv->mm.bound_list, global_list) {
		if (!obj->active && can_release_pages(obj))
			count += obj->base.size >> PAGE_SHIFT;
	}

	if (unlock)
		mutex_unlock(&dev->struct_mutex);

	return count;
}
