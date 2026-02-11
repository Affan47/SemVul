mpx_disable_management(void)
{
	struct mm_struct *mm = current->mm;

	if (!cpu_feature_enabled(X86_FEATURE_MPX))
		return -ENXIO;

	down_write(&mm->mmap_sem);
	mm->bd_addr = MPX_INVALID_BOUNDS_DIR;
	up_write(&mm->mmap_sem);
	return 0;
}
