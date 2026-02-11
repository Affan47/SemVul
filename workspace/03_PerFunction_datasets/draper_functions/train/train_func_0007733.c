dio_bio_complete(struct dio *dio, struct bio *bio)
{
	struct bio_vec *bvec;
	unsigned i;
	int err;

	if (bio->bi_error)
		dio->io_error = -EIO;

	if (dio->is_async && dio->rw == READ && dio->should_dirty) {
		err = bio->bi_error;
		bio_check_pages_dirty(bio);
	} else {
		bio_for_each_segment_all(bvec, bio, i) {
			struct page *page = bvec->bv_page;

			if (dio->rw == READ && !PageCompound(page) &&
					dio->should_dirty)
				set_page_dirty_lock(page);
			page_cache_release(page);
		}
		err = bio->bi_error;
		bio_put(bio);
	}
	return err;
}
