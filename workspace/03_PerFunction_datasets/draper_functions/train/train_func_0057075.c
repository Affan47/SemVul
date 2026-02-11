destroy_swap_extents(struct swap_info_struct *sis)
{
	while (!list_empty(&sis->first_swap_extent.list)) {
		struct swap_extent *se;

		se = list_entry(sis->first_swap_extent.list.next,
				struct swap_extent, list);
		list_del(&se->list);
		kfree(se);
	}

	if (sis->flags & SWP_FILE) {
		struct file *swap_file = sis->swap_file;
		struct address_space *mapping = swap_file->f_mapping;

		sis->flags &= ~SWP_FILE;
		mapping->a_ops->swap_deactivate(swap_file);
	}
}
