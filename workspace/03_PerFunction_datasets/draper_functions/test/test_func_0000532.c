allocate_bt(struct mm_struct *mm, long __user *bd_entry)
{
	unsigned long expected_old_val = 0;
	unsigned long actual_old_val = 0;
	unsigned long bt_addr;
	unsigned long bd_new_entry;
	int ret = 0;


	bt_addr = mpx_mmap(mpx_bt_size_bytes(mm));
	if (IS_ERR((void *)bt_addr))
		return PTR_ERR((void *)bt_addr);


	bd_new_entry = bt_addr | MPX_BD_ENTRY_VALID_FLAG;


	ret = mpx_cmpxchg_bd_entry(mm, &actual_old_val,	bd_entry,
				   expected_old_val, bd_new_entry);
	if (ret)
		goto out_unmap;


	if (actual_old_val & MPX_BD_ENTRY_VALID_FLAG) {
		ret = 0;
		goto out_unmap;
	}


	if (expected_old_val != actual_old_val) {
		ret = -EINVAL;
		goto out_unmap;
	}
	trace_mpx_new_bounds_table(bt_addr);
	return 0;
out_unmap:
	vm_munmap(bt_addr, mpx_bt_size_bytes(mm));
	return ret;
}
