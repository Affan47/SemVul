try_unmap_single_bt(struct mm_struct *mm,
	       unsigned long start, unsigned long end)
{
	struct vm_area_struct *next;
	struct vm_area_struct *prev;


	unsigned long bta_start_vaddr = start & ~(bd_entry_virt_space(mm)-1);
	unsigned long bta_end_vaddr = bta_start_vaddr + bd_entry_virt_space(mm);
	unsigned long uninitialized_var(bt_addr);
	void __user *bde_vaddr;
	int ret;


	next = find_vma_prev(mm, start, &prev);


	while (next && (next->vm_flags & VM_MPX))
		next = next->vm_next;
	while (prev && (prev->vm_flags & VM_MPX))
		prev = prev->vm_prev;


	next = find_vma_prev(mm, start, &prev);
	if ((!prev || prev->vm_end <= bta_start_vaddr) &&
	    (!next || next->vm_start >= bta_end_vaddr)) {


		start = bta_start_vaddr;
		end = bta_end_vaddr;
	}

	bde_vaddr = mm->bd_addr + mpx_get_bd_entry_offset(mm, start);
	ret = get_bt_addr(mm, bde_vaddr, &bt_addr);


	if (ret == -ENOENT) {
		ret = 0;
		return 0;
	}
	if (ret)
		return ret;


	if ((start == bta_start_vaddr) &&
	    (end == bta_end_vaddr))
		return unmap_entire_bt(mm, bde_vaddr, bt_addr);
	return zap_bt_entries_mapping(mm, bt_addr, start, end);
}
