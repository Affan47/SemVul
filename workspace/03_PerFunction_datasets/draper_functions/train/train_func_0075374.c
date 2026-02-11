drbd_bm_endio(struct bio *bio)
{
	struct drbd_bm_aio_ctx *ctx = bio->bi_private;
	struct drbd_device *device = ctx->device;
	struct drbd_bitmap *b = device->bitmap;
	unsigned int idx = bm_page_to_idx(bio->bi_io_vec[0].bv_page);

	if ((ctx->flags & BM_AIO_COPY_PAGES) == 0 &&
	    !bm_test_page_unchanged(b->bm_pages[idx]))
		drbd_warn(device, "bitmap page idx %u changed during IO!\n", idx);

	if (bio->bi_error) {


		ctx->error = bio->bi_error;
		bm_set_page_io_err(b->bm_pages[idx]);


		if (__ratelimit(&drbd_ratelimit_state))
			drbd_err(device, "IO ERROR %d on bitmap page idx %u\n",
					bio->bi_error, idx);
	} else {
		bm_clear_page_io_err(b->bm_pages[idx]);
		dynamic_drbd_dbg(device, "bitmap page idx %u completed\n", idx);
	}

	bm_page_unlock_io(device, idx);

	if (ctx->flags & BM_AIO_COPY_PAGES)
		mempool_free(bio->bi_io_vec[0].bv_page, drbd_md_io_page_pool);

	bio_put(bio);

	if (atomic_dec_and_test(&ctx->in_flight)) {
		ctx->done = 1;
		wake_up(&device->misc_wait);
		kref_put(&ctx->kref, &drbd_bm_aio_ctx_destroy);
	}
}
