__set_page_dirty_nobuffers(struct page *page)
{
	struct mem_cgroup *memcg;

	memcg = mem_cgroup_begin_page_stat(page);
	if (!TestSetPageDirty(page)) {
		struct address_space *mapping = page_mapping(page);
		unsigned long flags;

		if (!mapping) {
			mem_cgroup_end_page_stat(memcg);
			return 1;
		}

		spin_lock_irqsave(&mapping->tree_lock, flags);
		BUG_ON(page_mapping(page) != mapping);
		WARN_ON_ONCE(!PagePrivate(page) && !PageUptodate(page));
		account_page_dirtied(page, mapping, memcg);
		radix_tree_tag_set(&mapping->page_tree, page_index(page),
				   PAGECACHE_TAG_DIRTY);
		spin_unlock_irqrestore(&mapping->tree_lock, flags);
		mem_cgroup_end_page_stat(memcg);

		if (mapping->host) {

			__mark_inode_dirty(mapping->host, I_DIRTY_PAGES);
		}
		return 1;
	}
	mem_cgroup_end_page_stat(memcg);
	return 0;
}
