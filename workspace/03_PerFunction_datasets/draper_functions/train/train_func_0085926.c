i915_gem_load_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int i;

	dev_priv->objects =
		kmem_cache_create("i915_gem_object",
				  sizeof(struct drm_i915_gem_object), 0,
				  SLAB_HWCACHE_ALIGN,
				  NULL);
	dev_priv->vmas =
		kmem_cache_create("i915_gem_vma",
				  sizeof(struct i915_vma), 0,
				  SLAB_HWCACHE_ALIGN,
				  NULL);
	dev_priv->requests =
		kmem_cache_create("i915_gem_request",
				  sizeof(struct drm_i915_gem_request), 0,
				  SLAB_HWCACHE_ALIGN,
				  NULL);

	INIT_LIST_HEAD(&dev_priv->vm_list);
	INIT_LIST_HEAD(&dev_priv->context_list);
	INIT_LIST_HEAD(&dev_priv->mm.unbound_list);
	INIT_LIST_HEAD(&dev_priv->mm.bound_list);
	INIT_LIST_HEAD(&dev_priv->mm.fence_list);
	for (i = 0; i < I915_NUM_ENGINES; i++)
		init_engine_lists(&dev_priv->engine[i]);
	for (i = 0; i < I915_MAX_NUM_FENCES; i++)
		INIT_LIST_HEAD(&dev_priv->fence_regs[i].lru_list);
	INIT_DELAYED_WORK(&dev_priv->mm.retire_work,
			  i915_gem_retire_work_handler);
	INIT_DELAYED_WORK(&dev_priv->mm.idle_work,
			  i915_gem_idle_work_handler);
	init_waitqueue_head(&dev_priv->gpu_error.reset_queue);

	dev_priv->relative_constants_mode = I915_EXEC_CONSTANTS_REL_GENERAL;


	dev_priv->next_seqno = ((u32)~0 - 0x1100);
	dev_priv->last_seqno = ((u32)~0 - 0x1101);

	INIT_LIST_HEAD(&dev_priv->mm.fence_list);

	init_waitqueue_head(&dev_priv->pending_flip_queue);

	dev_priv->mm.interruptible = true;

	mutex_init(&dev_priv->fb_tracking.lock);
}
