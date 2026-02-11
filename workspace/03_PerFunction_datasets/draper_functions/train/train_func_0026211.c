radeon_gem_op_ioctl(struct drm_device *dev, void *data,
			struct drm_file *filp)
{
	struct drm_radeon_gem_op *args = data;
	struct drm_gem_object *gobj;
	struct radeon_bo *robj;
	int r;

	gobj = drm_gem_object_lookup(dev, filp, args->handle);
	if (gobj == NULL) {
		return -ENOENT;
	}
	robj = gem_to_radeon_bo(gobj);

	r = -EPERM;
	if (radeon_ttm_tt_has_userptr(robj->tbo.ttm))
		goto out;

	r = radeon_bo_reserve(robj, false);
	if (unlikely(r))
		goto out;

	switch (args->op) {
	case RADEON_GEM_OP_GET_INITIAL_DOMAIN:
		args->value = robj->initial_domain;
		break;
	case RADEON_GEM_OP_SET_INITIAL_DOMAIN:
		robj->initial_domain = args->value & (RADEON_GEM_DOMAIN_VRAM |
						      RADEON_GEM_DOMAIN_GTT |
						      RADEON_GEM_DOMAIN_CPU);
		break;
	default:
		r = -EINVAL;
	}

	radeon_bo_unreserve(robj);
out:
	drm_gem_object_unreference_unlocked(gobj);
	return r;
}
