swap_info_get(swp_entry_t entry)
{
	struct swap_info_struct *p;
	unsigned long offset, type;

	if (!entry.val)
		goto out;
	type = swp_type(entry);
	if (type >= nr_swapfiles)
		goto bad_nofile;
	p = swap_info[type];
	if (!(p->flags & SWP_USED))
		goto bad_device;
	offset = swp_offset(entry);
	if (offset >= p->max)
		goto bad_offset;
	if (!p->swap_map[offset])
		goto bad_free;
	spin_lock(&p->lock);
	return p;

bad_free:
	pr_err("swap_free: %s%08lx\n", Unused_offset, entry.val);
	goto out;
bad_offset:
	pr_err("swap_free: %s%08lx\n", Bad_offset, entry.val);
	goto out;
bad_device:
	pr_err("swap_free: %s%08lx\n", Unused_file, entry.val);
	goto out;
bad_nofile:
	pr_err("swap_free: %s%08lx\n", Bad_file, entry.val);
out:
	return NULL;
}
