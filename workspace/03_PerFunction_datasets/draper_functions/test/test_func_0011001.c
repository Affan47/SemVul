amdgpu_vm_bo_rmv(struct amdgpu_device *adev,
		      struct amdgpu_bo_va *bo_va)
{
	struct amdgpu_bo_va_mapping *mapping, *next;
	struct amdgpu_vm *vm = bo_va->vm;

	list_del(&bo_va->bo_list);

	spin_lock(&vm->status_lock);
	list_del(&bo_va->vm_status);
	spin_unlock(&vm->status_lock);

	list_for_each_entry_safe(mapping, next, &bo_va->valids, list) {
		list_del(&mapping->list);
		spin_lock(&vm->it_lock);
		interval_tree_remove(&mapping->it, &vm->va);
		spin_unlock(&vm->it_lock);
		trace_amdgpu_vm_bo_unmap(bo_va, mapping);
		spin_lock(&vm->freed_lock);
		list_add(&mapping->list, &vm->freed);
		spin_unlock(&vm->freed_lock);
	}
	list_for_each_entry_safe(mapping, next, &bo_va->invalids, list) {
		list_del(&mapping->list);
		spin_lock(&vm->it_lock);
		interval_tree_remove(&mapping->it, &vm->va);
		spin_unlock(&vm->it_lock);
		kfree(mapping);
	}
	fence_put(bo_va->last_pt_update);
	mutex_destroy(&bo_va->mutex);
	kfree(bo_va);
}
