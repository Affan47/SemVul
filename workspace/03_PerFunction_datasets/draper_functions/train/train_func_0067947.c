__ntfs_grab_cache_pages(struct address_space *mapping,
		pgoff_t index, const unsigned nr_pages, struct page **pages,
		struct page **cached_page)
{
	int err, nr;

	BUG_ON(!nr_pages);
	err = nr = 0;
	do {
		pages[nr] = find_get_page_flags(mapping, index, FGP_LOCK |
				FGP_ACCESSED);
		if (!pages[nr]) {
			if (!*cached_page) {
				*cached_page = page_cache_alloc(mapping);
				if (unlikely(!*cached_page)) {
					err = -ENOMEM;
					goto err_out;
				}
			}
			err = add_to_page_cache_lru(*cached_page, mapping,
				   index,
				   mapping_gfp_constraint(mapping, GFP_KERNEL));
			if (unlikely(err)) {
				if (err == -EEXIST)
					continue;
				goto err_out;
			}
			pages[nr] = *cached_page;
			*cached_page = NULL;
		}
		index++;
		nr++;
	} while (nr < nr_pages);
out:
	return err;
err_out:
	while (nr > 0) {
		unlock_page(pages[--nr]);
		page_cache_release(pages[nr]);
	}
	goto out;
}
