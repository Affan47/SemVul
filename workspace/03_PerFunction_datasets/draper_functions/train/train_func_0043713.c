udl_gem_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct udl_gem_object *obj = to_udl_bo(vma->vm_private_data);
	struct page *page;
	unsigned int page_offset;
	int ret = 0;

	page_offset = ((unsigned long)vmf->virtual_address - vma->vm_start) >>
		PAGE_SHIFT;

	if (!obj->pages)
		return VM_FAULT_SIGBUS;

	page = obj->pages[page_offset];
	ret = vm_insert_page(vma, (unsigned long)vmf->virtual_address, page);
	switch (ret) {
	case -EAGAIN:
	case 0:
	case -ERESTARTSYS:
		return VM_FAULT_NOPAGE;
	case -ENOMEM:
		return VM_FAULT_OOM;
	default:
		return VM_FAULT_SIGBUS;
	}
}
