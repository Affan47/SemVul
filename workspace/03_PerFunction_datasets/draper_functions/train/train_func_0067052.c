btt_make_request(struct request_queue *q, struct bio *bio)
{
	struct bio_integrity_payload *bip = bio_integrity(bio);
	struct btt *btt = q->queuedata;
	struct bvec_iter iter;
	unsigned long start;
	struct bio_vec bvec;
	int err = 0, rw;
	bool do_acct;


	if (bio_integrity_enabled(bio) && bio_integrity_prep(bio)) {
		bio->bi_error = -EIO;
		goto out;
	}

	do_acct = nd_iostat_start(bio, &start);
	rw = bio_data_dir(bio);
	bio_for_each_segment(bvec, bio, iter) {
		unsigned int len = bvec.bv_len;

		BUG_ON(len > PAGE_SIZE);


		BUG_ON(len < btt->sector_size);
		BUG_ON(len % btt->sector_size);

		err = btt_do_bvec(btt, bip, bvec.bv_page, len, bvec.bv_offset,
				rw, iter.bi_sector);
		if (err) {
			dev_info(&btt->nd_btt->dev,
					"io error in %s sector %lld, len %d,\n",
					(rw == READ) ? "READ" : "WRITE",
					(unsigned long long) iter.bi_sector, len);
			bio->bi_error = err;
			break;
		}
	}
	if (do_acct)
		nd_iostat_end(bio, start);

out:
	bio_endio(bio);
	return BLK_QC_T_NONE;
}
