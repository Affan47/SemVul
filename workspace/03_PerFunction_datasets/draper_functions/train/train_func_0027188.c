i915_gem_object_create_stolen_for_preallocated(struct drm_device *dev,
					       u32 stolen_offset,
					       u32 gtt_offset,
					       u32 size)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct i915_address_space *ggtt = &dev_priv->gtt.base;
	struct drm_i915_gem_object *obj;
	struct drm_mm_node *stolen;
	struct i915_vma *vma;
	int ret;

	if (!drm_mm_initialized(&dev_priv->mm.stolen))
		return NULL;

	DRM_DEBUG_KMS("creating preallocated stolen object: stolen_offset=%x, gtt_offset=%x, size=%x\n",
			stolen_offset, gtt_offset, size);


	if (WARN_ON(size == 0) || WARN_ON(size & 4095) ||
	    WARN_ON(stolen_offset & 4095))
		return NULL;

	stolen = kzalloc(sizeof(*stolen), GFP_KERNEL);
	if (!stolen)
		return NULL;

	stolen->start = stolen_offset;
	stolen->size = size;
	mutex_lock(&dev_priv->mm.stolen_lock);
	ret = drm_mm_reserve_node(&dev_priv->mm.stolen, stolen);
	mutex_unlock(&dev_priv->mm.stolen_lock);
	if (ret) {
		DRM_DEBUG_KMS("failed to allocate stolen space\n");
		kfree(stolen);
		return NULL;
	}

	obj = _i915_gem_object_create_stolen(dev, stolen);
	if (obj == NULL) {
		DRM_DEBUG_KMS("failed to allocate stolen object\n");
		i915_gem_stolen_remove_node(dev_priv, stolen);
		kfree(stolen);
		return NULL;
	}


	if (gtt_offset == I915_GTT_OFFSET_NONE)
		return obj;

	vma = i915_gem_obj_lookup_or_create_vma(obj, ggtt);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto err;
	}


	vma->node.start = gtt_offset;
	vma->node.size = size;
	if (drm_mm_initialized(&ggtt->mm)) {
		ret = drm_mm_reserve_node(&ggtt->mm, &vma->node);
		if (ret) {
			DRM_DEBUG_KMS("failed to allocate stolen GTT space\n");
			goto err;
		}

		vma->bound |= GLOBAL_BIND;
		__i915_vma_set_map_and_fenceable(vma);
		list_add_tail(&vma->mm_list, &ggtt->inactive_list);
	}

	list_add_tail(&obj->global_list, &dev_priv->mm.bound_list);
	i915_gem_object_pin_pages(obj);

	return obj;

err:
	drm_gem_object_unreference(&obj->base);
	return NULL;
}
