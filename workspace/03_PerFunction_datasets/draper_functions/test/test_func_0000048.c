btrfs_clone_extent_buffer(struct extent_buffer *src)
{
	unsigned long i;
	struct page *p;
	struct extent_buffer *new;
	unsigned long num_pages = num_extent_pages(src->start, src->len);

	new = __alloc_extent_buffer(src->fs_info, src->start, src->len);
	if (new == NULL)
		return NULL;

	for (i = 0; i < num_pages; i++) {
		p = alloc_page(GFP_NOFS);
		if (!p) {
			btrfs_release_extent_buffer(new);
			return NULL;
		}
		attach_extent_buffer_page(new, p);
		WARN_ON(PageDirty(p));
		SetPageUptodate(p);
		new->pages[i] = p;
	}

	copy_extent_buffer(new, src, 0, 0, src->len);
	set_bit(EXTENT_BUFFER_UPTODATE, &new->bflags);
	set_bit(EXTENT_BUFFER_DUMMY, &new->bflags);

	return new;
}
