i915_gem_userptr_release__mmu_notifier(struct drm_i915_gem_object *obj)
{
	struct i915_mmu_object *mo;

	mo = obj->userptr.mmu_object;
	if (mo == NULL)
		return;

	i915_mmu_notifier_del(mo->mn, mo);
	kfree(mo);

	obj->userptr.mmu_object = NULL;
}
