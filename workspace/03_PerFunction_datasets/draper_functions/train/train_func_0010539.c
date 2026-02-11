in_user_stack(ulong task, ulong vaddr)
{
	ulong vma;
	ulonglong vm_flags;
	char *vma_buf;

	if ((vma = vm_area_dump(task, UVADDR|VERIFY_ADDR, vaddr, 0))) {
		vma_buf = fill_vma_cache(vma);
		vm_flags = get_vm_flags(vma_buf);

		if (vm_flags & VM_GROWSDOWN)
			return TRUE;
		else if (kernel_symbol_exists("expand_upwards") &&
			(vm_flags & VM_GROWSUP))
			return TRUE;


		if ((vm_flags & (VM_READ|VM_WRITE)) == (VM_READ|VM_WRITE))
			return TRUE;
	}
	return FALSE;
}
