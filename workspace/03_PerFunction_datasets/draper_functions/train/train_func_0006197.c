radeon_bo_vm_update_pte(struct radeon_cs_parser *p,
				   struct radeon_vm *vm)
{
	struct radeon_device *rdev = p->rdev;
	struct radeon_bo_va *bo_va;
	int i, r;

	r = radeon_vm_update_page_directory(rdev, vm);
	if (r)
		return r;

	r = radeon_vm_clear_freed(rdev, vm);
	if (r)
		return r;

	if (vm->ib_bo_va == NULL) {
		DRM_ERROR("Tmp BO not in VM!\n");
		return -EINVAL;
	}

	r = radeon_vm_bo_update(rdev, vm->ib_bo_va,
				&rdev->ring_tmp_bo.bo->tbo.mem);
	if (r)
		return r;

	for (i = 0; i < p->nrelocs; i++) {
		struct radeon_bo *bo;

		bo = p->relocs[i].robj;
		bo_va = radeon_vm_bo_find(vm, bo);
		if (bo_va == NULL) {
			dev_err(rdev->dev, "bo %p not in vm %p\n", bo, vm);
			return -EINVAL;
		}

		r = radeon_vm_bo_update(rdev, bo_va, &bo->tbo.mem);
		if (r)
			return r;

		radeon_sync_fence(&p->ib.sync, bo_va->last_pt_update);
	}

	return radeon_vm_clear_invalids(rdev, vm);
}
