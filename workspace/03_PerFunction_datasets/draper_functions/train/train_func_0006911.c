sgl_map_user_pages(struct st_buffer *STbp,
			      const unsigned int max_pages, unsigned long uaddr,
			      size_t count, int rw)
{
	unsigned long end = (uaddr + count + PAGE_SIZE - 1) >> PAGE_SHIFT;
	unsigned long start = uaddr >> PAGE_SHIFT;
	const int nr_pages = end - start;
	int res, i, j;
	struct page **pages;
	struct rq_map_data *mdata = &STbp->map_data;


	if ((uaddr + count) < uaddr)
		return -EINVAL;


        if (nr_pages > max_pages)
		return -ENOMEM;


	if (count == 0)
		return 0;

	if ((pages = kmalloc(max_pages * sizeof(*pages), GFP_KERNEL)) == NULL)
		return -ENOMEM;


	res = get_user_pages_unlocked(
		current,
		current->mm,
		uaddr,
		nr_pages,
		rw == READ,
		0,
		pages);


	if (res < nr_pages)
		goto out_unmap;

        for (i=0; i < nr_pages; i++) {


		flush_dcache_page(pages[i]);
        }

	mdata->offset = uaddr & ~PAGE_MASK;
	STbp->mapped_pages = pages;

	return nr_pages;
 out_unmap:
	if (res > 0) {
		for (j=0; j < res; j++)
			page_cache_release(pages[j]);
		res = 0;
	}
	kfree(pages);
	return res;
}
