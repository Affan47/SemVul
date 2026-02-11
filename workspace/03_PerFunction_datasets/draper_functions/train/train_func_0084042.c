scrub_add_page_to_wr_bio(struct scrub_ctx *sctx,
				    struct scrub_page *spage)
{
	struct scrub_wr_ctx *wr_ctx = &sctx->wr_ctx;
	struct scrub_bio *sbio;
	int ret;

	mutex_lock(&wr_ctx->wr_lock);
again:
	if (!wr_ctx->wr_curr_bio) {
		wr_ctx->wr_curr_bio = kzalloc(sizeof(*wr_ctx->wr_curr_bio),
					      GFP_NOFS);
		if (!wr_ctx->wr_curr_bio) {
			mutex_unlock(&wr_ctx->wr_lock);
			return -ENOMEM;
		}
		wr_ctx->wr_curr_bio->sctx = sctx;
		wr_ctx->wr_curr_bio->page_count = 0;
	}
	sbio = wr_ctx->wr_curr_bio;
	if (sbio->page_count == 0) {
		struct bio *bio;

		sbio->physical = spage->physical_for_dev_replace;
		sbio->logical = spage->logical;
		sbio->dev = wr_ctx->tgtdev;
		bio = sbio->bio;
		if (!bio) {
			bio = btrfs_io_bio_alloc(GFP_NOFS, wr_ctx->pages_per_wr_bio);
			if (!bio) {
				mutex_unlock(&wr_ctx->wr_lock);
				return -ENOMEM;
			}
			sbio->bio = bio;
		}

		bio->bi_private = sbio;
		bio->bi_end_io = scrub_wr_bio_end_io;
		bio->bi_bdev = sbio->dev->bdev;
		bio->bi_iter.bi_sector = sbio->physical >> 9;
		sbio->err = 0;
	} else if (sbio->physical + sbio->page_count * PAGE_SIZE !=
		   spage->physical_for_dev_replace ||
		   sbio->logical + sbio->page_count * PAGE_SIZE !=
		   spage->logical) {
		scrub_wr_submit(sctx);
		goto again;
	}

	ret = bio_add_page(sbio->bio, spage->page, PAGE_SIZE, 0);
	if (ret != PAGE_SIZE) {
		if (sbio->page_count < 1) {
			bio_put(sbio->bio);
			sbio->bio = NULL;
			mutex_unlock(&wr_ctx->wr_lock);
			return -EIO;
		}
		scrub_wr_submit(sctx);
		goto again;
	}

	sbio->pagev[sbio->page_count] = spage;
	scrub_page_get(spage);
	sbio->page_count++;
	if (sbio->page_count == wr_ctx->pages_per_wr_bio)
		scrub_wr_submit(sctx);
	mutex_unlock(&wr_ctx->wr_lock);

	return 0;
}
