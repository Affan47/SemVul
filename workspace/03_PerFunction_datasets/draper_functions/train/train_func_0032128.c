__set_page_dirty_buffers(struct page *page)
{
	int newly_dirty;
	struct mem_cgroup *memcg;
	struct address_space *mapping = page_mapping(page);

	if (unlikely(!mapping))
		return !TestSetPageDirty(page);

	spin_lock(&mapping->private_lock);
	if (page_has_buffers(page)) {
		struct buffer_head *head = page_buffers(page);
		struct buffer_head *bh = head;

		do {
			set_buffer_dirty(bh);
			bh = bh->b_this_page;
		} while (bh != head);
	}


	memcg = mem_cgroup_begin_page_stat(page);
	newly_dirty = !TestSetPageDirty(page);
	spin_unlock(&mapping->private_lock);

	if (newly_dirty)
		__set_page_dirty(page, mapping, memcg, 1);

	mem_cgroup_end_page_stat(memcg);

	if (newly_dirty)
		__mark_inode_dirty(mapping->host, I_DIRTY_PAGES);

	return newly_dirty;
}
