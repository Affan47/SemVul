free_memtype(u64 start, u64 end)
{
	int err = -EINVAL;
	int is_range_ram;
	struct memtype *entry;

	if (!pat_enabled())
		return 0;


	if (x86_platform.is_untracked_pat_range(start, end))
		return 0;

	is_range_ram = pat_pagerange_is_ram(start, end);
	if (is_range_ram == 1) {

		err = free_ram_pages_type(start, end);

		return err;
	} else if (is_range_ram < 0) {
		return -EINVAL;
	}

	spin_lock(&memtype_lock);
	entry = rbt_memtype_erase(start, end);
	spin_unlock(&memtype_lock);

	if (!entry) {
		pr_info("x86/PAT: %s:%d freeing invalid memtype [mem %#010Lx-%#010Lx]\n",
			current->comm, current->pid, start, end - 1);
		return -EINVAL;
	}

	kfree(entry);

	dprintk("free_memtype request [mem %#010Lx-%#010Lx]\n", start, end - 1);

	return 0;
}
