write_sb_page(struct bitmap *bitmap, struct page *page, int wait)
{
	struct md_rdev *rdev = NULL;
	struct block_device *bdev;
	struct mddev *mddev = bitmap->mddev;
	struct bitmap_storage *store = &bitmap->storage;
	int node_offset = 0;

	if (mddev_is_clustered(bitmap->mddev))
		node_offset = bitmap->cluster_slot * store->file_pages;

	while ((rdev = next_active_rdev(rdev, mddev)) != NULL) {
		int size = PAGE_SIZE;
		loff_t offset = mddev->bitmap_info.offset;

		bdev = (rdev->meta_bdev) ? rdev->meta_bdev : rdev->bdev;

		if (page->index == store->file_pages-1) {
			int last_page_size = store->bytes & (PAGE_SIZE-1);
			if (last_page_size == 0)
				last_page_size = PAGE_SIZE;
			size = roundup(last_page_size,
				       bdev_logical_block_size(bdev));
		}


		if (mddev->external) {

			if (rdev->sb_start + offset + (page->index
						       * (PAGE_SIZE/512))
			    > rdev->data_offset
			    &&
			    rdev->sb_start + offset
			    < (rdev->data_offset + mddev->dev_sectors
			     + (PAGE_SIZE/512)))
				goto bad_alignment;
		} else if (offset < 0) {

			if (offset
			    + (long)(page->index * (PAGE_SIZE/512))
			    + size/512 > 0)

				goto bad_alignment;
			if (rdev->data_offset + mddev->dev_sectors
			    > rdev->sb_start + offset)

				goto bad_alignment;
		} else if (rdev->sb_start < rdev->data_offset) {

			if (rdev->sb_start
			    + offset
			    + page->index*(PAGE_SIZE/512) + size/512
			    > rdev->data_offset)

				goto bad_alignment;
		} else {

		}
		md_super_write(mddev, rdev,
			       rdev->sb_start + offset
			       + page->index * (PAGE_SIZE/512),
			       size,
			       page);
	}

	if (wait)
		md_super_wait(mddev);
	return 0;

 bad_alignment:
	return -EINVAL;
}
