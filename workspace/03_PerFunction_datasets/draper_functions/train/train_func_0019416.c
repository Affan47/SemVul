shmem_pread_slow(struct page *page, int shmem_page_offset, int page_length,
		 char __user *user_data,
		 bool page_do_bit17_swizzling, bool needs_clflush)
{
	char *vaddr;
	int ret;

	vaddr = kmap(page);
	if (needs_clflush)
		shmem_clflush_swizzled_range(vaddr + shmem_page_offset,
					     page_length,
					     page_do_bit17_swizzling);

	if (page_do_bit17_swizzling)
		ret = __copy_to_user_swizzled(user_data,
					      vaddr, shmem_page_offset,
					      page_length);
	else
		ret = __copy_to_user(user_data,
				     vaddr + shmem_page_offset,
				     page_length);
	kunmap(page);

	return ret ? - EFAULT : 0;
}
