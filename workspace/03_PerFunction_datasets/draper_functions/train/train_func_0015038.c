cancel_userptr(struct work_struct *work)
{
	struct i915_mmu_object *mo = container_of(work, typeof(*mo), work);
	struct drm_i915_gem_object *obj = mo->obj;
	struct drm_device *dev = obj->base.dev;

	mutex_lock(&dev->struct_mutex);

	obj->userptr.work = NULL;

	if (obj->pages != NULL) {
		struct drm_i915_private *dev_priv = to_i915(dev);
		struct i915_vma *vma, *tmp;
		bool was_interruptible;

		wait_rendering(obj);

		was_interruptible = dev_priv->mm.interruptible;
		dev_priv->mm.interruptible = false;

		list_for_each_entry_safe(vma, tmp, &obj->vma_list, obj_link)
			WARN_ON(i915_vma_unbind(vma));
		WARN_ON(i915_gem_object_put_pages(obj));

		dev_priv->mm.interruptible = was_interruptible;
	}

	drm_gem_object_unreference(&obj->base);
	mutex_unlock(&dev->struct_mutex);
}
