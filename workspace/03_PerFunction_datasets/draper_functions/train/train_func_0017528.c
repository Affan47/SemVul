radeon_gem_userptr_ioctl(struct drm_device *dev, void *data,
			     struct drm_file *filp)
{
	struct radeon_device *rdev = dev->dev_private;
	struct drm_radeon_gem_userptr *args = data;
	struct drm_gem_object *gobj;
	struct radeon_bo *bo;
	uint32_t handle;
	int r;

	if (offset_in_page(args->addr | args->size))
		return -EINVAL;


	if (args->flags & ~(RADEON_GEM_USERPTR_READONLY |
	    RADEON_GEM_USERPTR_ANONONLY | RADEON_GEM_USERPTR_VALIDATE |
	    RADEON_GEM_USERPTR_REGISTER))
		return -EINVAL;

	if (args->flags & RADEON_GEM_USERPTR_READONLY) {

		if (rdev->family < CHIP_R600)
			return -EINVAL;

	} else if (!(args->flags & RADEON_GEM_USERPTR_ANONONLY) ||
		   !(args->flags & RADEON_GEM_USERPTR_REGISTER)) {


		return -EACCES;
	}

	down_read(&rdev->exclusive_lock);


	r = radeon_gem_object_create(rdev, args->size, 0,
				     RADEON_GEM_DOMAIN_CPU, 0,
				     false, &gobj);
	if (r)
		goto handle_lockup;

	bo = gem_to_radeon_bo(gobj);
	r = radeon_ttm_tt_set_userptr(bo->tbo.ttm, args->addr, args->flags);
	if (r)
		goto release_object;

	if (args->flags & RADEON_GEM_USERPTR_REGISTER) {
		r = radeon_mn_register(bo, args->addr);
		if (r)
			goto release_object;
	}

	if (args->flags & RADEON_GEM_USERPTR_VALIDATE) {
		down_read(&current->mm->mmap_sem);
		r = radeon_bo_reserve(bo, true);
		if (r) {
			up_read(&current->mm->mmap_sem);
			goto release_object;
		}

		radeon_ttm_placement_from_domain(bo, RADEON_GEM_DOMAIN_GTT);
		r = ttm_bo_validate(&bo->tbo, &bo->placement, true, false);
		radeon_bo_unreserve(bo);
		up_read(&current->mm->mmap_sem);
		if (r)
			goto release_object;
	}

	r = drm_gem_handle_create(filp, gobj, &handle);

	drm_gem_object_unreference_unlocked(gobj);
	if (r)
		goto handle_lockup;

	args->handle = handle;
	up_read(&rdev->exclusive_lock);
	return 0;

release_object:
	drm_gem_object_unreference_unlocked(gobj);

handle_lockup:
	up_read(&rdev->exclusive_lock);
	r = radeon_gem_handle_lockup(rdev, r);

	return r;
}
