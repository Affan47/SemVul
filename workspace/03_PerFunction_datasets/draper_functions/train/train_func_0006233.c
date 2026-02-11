amdgpu_gem_object_open(struct drm_gem_object *obj, struct drm_file *file_priv)
{
	struct amdgpu_bo *rbo = gem_to_amdgpu_bo(obj);
	struct amdgpu_device *adev = rbo->adev;
	struct amdgpu_fpriv *fpriv = file_priv->driver_priv;
	struct amdgpu_vm *vm = &fpriv->vm;
	struct amdgpu_bo_va *bo_va;
	int r;
	r = amdgpu_bo_reserve(rbo, false);
	if (r)
		return r;

	bo_va = amdgpu_vm_bo_find(vm, rbo);
	if (!bo_va) {
		bo_va = amdgpu_vm_bo_add(adev, vm, rbo);
	} else {
		++bo_va->ref_count;
	}
	amdgpu_bo_unreserve(rbo);
	return 0;
}
