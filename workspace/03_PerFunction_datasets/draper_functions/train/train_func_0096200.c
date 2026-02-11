amdgpu_vm_bo_unmap(struct amdgpu_device *adev,
		       struct amdgpu_bo_va *bo_va,
		       uint64_t saddr)
{
	struct amdgpu_bo_va_mapping *mapping;
	struct amdgpu_vm *vm = bo_va->vm;
	bool valid = true;

	saddr /= AMDGPU_GPU_PAGE_SIZE;
	mutex_lock(&bo_va->mutex);
	list_for_each_entry(mapping, &bo_va->valids, list) {
		if (mapping->it.start == saddr)
			break;
	}

	if (&mapping->list == &bo_va->valids) {
		valid = false;

		list_for_each_entry(mapping, &bo_va->invalids, list) {
			if (mapping->it.start == saddr)
				break;
		}

		if (&mapping->list == &bo_va->invalids) {
			mutex_unlock(&bo_va->mutex);
			return -ENOENT;
		}
	}
	mutex_unlock(&bo_va->mutex);
	list_del(&mapping->list);
	spin_lock(&vm->it_lock);
	interval_tree_remove(&mapping->it, &vm->va);
	spin_unlock(&vm->it_lock);
	trace_amdgpu_vm_bo_unmap(bo_va, mapping);

	if (valid) {
		spin_lock(&vm->freed_lock);
		list_add(&mapping->list, &vm->freed);
		spin_unlock(&vm->freed_lock);
	} else {
		kfree(mapping);
	}

	return 0;
}
