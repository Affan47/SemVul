zap_bt_entries_mapping(struct mm_struct *mm,
		unsigned long bt_addr,
		unsigned long start_mapping, unsigned long end_mapping)
{
	struct vm_area_struct *vma;
	unsigned long addr, len;
	unsigned long start;
	unsigned long end;


	start = bt_addr + mpx_get_bt_entry_offset_bytes(mm, start_mapping);
	end   = bt_addr + mpx_get_bt_entry_offset_bytes(mm, end_mapping - 1);


	end += bt_entry_size_bytes(mm);


	vma = find_vma(mm, start);
	if (!vma || vma->vm_start > start)
		return -EINVAL;


	addr = start;
	while (vma && vma->vm_start < end) {


		if (!(vma->vm_flags & VM_MPX))
			return -EINVAL;

		len = min(vma->vm_end, end) - addr;
		zap_page_range(vma, addr, len, NULL);
		trace_mpx_unmap_zap(addr, addr+len);

		vma = vma->vm_next;
		addr = vma->vm_start;
	}
	return 0;
}
