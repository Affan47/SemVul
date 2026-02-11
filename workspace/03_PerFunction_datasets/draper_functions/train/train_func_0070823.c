i915_gem_userptr_get_pages(struct drm_i915_gem_object *obj)
{
	const int num_pages = obj->base.size >> PAGE_SHIFT;
	struct page **pvec;
	int pinned, ret;
	bool active;


	if (IS_ERR(obj->userptr.work)) {

		ret = PTR_ERR(obj->userptr.work);
		obj->userptr.work = NULL;
		return ret;
	}
	if (obj->userptr.work)

		return -EAGAIN;


	ret = __i915_gem_userptr_set_active(obj, true);
	if (ret)
		return ret;

	pvec = NULL;
	pinned = 0;
	if (obj->userptr.mm->mm == current->mm) {
		pvec = drm_malloc_gfp(num_pages, sizeof(struct page *),
				      GFP_TEMPORARY);
		if (pvec == NULL) {
			__i915_gem_userptr_set_active(obj, false);
			return -ENOMEM;
		}

		pinned = __get_user_pages_fast(obj->userptr.ptr, num_pages,
					       !obj->userptr.read_only, pvec);
	}

	active = false;
	if (pinned < 0)
		ret = pinned, pinned = 0;
	else if (pinned < num_pages)
		ret = __i915_gem_userptr_get_pages_schedule(obj, &active);
	else
		ret = __i915_gem_userptr_set_pages(obj, pvec, num_pages);
	if (ret) {
		__i915_gem_userptr_set_active(obj, active);
		release_pages(pvec, pinned, 0);
	}
	drm_free_large(pvec);
	return ret;
}
