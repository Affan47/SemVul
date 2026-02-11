get_swap_bio(gfp_t gfp_flags,
				struct page *page, bio_end_io_t end_io)
{
	struct bio *bio;

	bio = bio_alloc(gfp_flags, 1);
	if (bio) {
		bio->bi_iter.bi_sector = map_swap_page(page, &bio->bi_bdev);
		bio->bi_iter.bi_sector <<= PAGE_SHIFT - 9;
		bio->bi_end_io = end_io;

		bio_add_page(bio, page, PAGE_SIZE, 0);
		BUG_ON(bio->bi_iter.bi_size != PAGE_SIZE);
	}
	return bio;
}
