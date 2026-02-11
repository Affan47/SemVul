nouveau_bo_vma_add(struct nouveau_bo *nvbo, struct nvkm_vm *vm,
		   struct nvkm_vma *vma)
{
	const u32 size = nvbo->bo.mem.num_pages << PAGE_SHIFT;
	int ret;

	ret = nvkm_vm_get(vm, size, nvbo->page_shift,
			     NV_MEM_ACCESS_RW, vma);
	if (ret)
		return ret;

	if ( nvbo->bo.mem.mem_type != TTM_PL_SYSTEM &&
	    (nvbo->bo.mem.mem_type == TTM_PL_VRAM ||
	     nvbo->page_shift != vma->vm->mmu->lpg_shift))
		nvkm_vm_map(vma, nvbo->bo.mem.mm_node);

	list_add_tail(&vma->head, &nvbo->vma_list);
	vma->refcount = 1;
	return 0;
}
