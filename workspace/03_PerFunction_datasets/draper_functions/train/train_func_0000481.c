blk_rq_count_integrity_sg(struct request_queue *q, struct bio *bio)
{
	struct bio_vec iv, ivprv = { NULL };
	unsigned int segments = 0;
	unsigned int seg_size = 0;
	struct bvec_iter iter;
	int prev = 0;

	bio_for_each_integrity_vec(iv, bio, iter) {

		if (prev) {
			if (!BIOVEC_PHYS_MERGEABLE(&ivprv, &iv))
				goto new_segment;

			if (!BIOVEC_SEG_BOUNDARY(q, &ivprv, &iv))
				goto new_segment;

			if (seg_size + iv.bv_len > queue_max_segment_size(q))
				goto new_segment;

			seg_size += iv.bv_len;
		} else {
new_segment:
			segments++;
			seg_size = iv.bv_len;
		}

		prev = 1;
		ivprv = iv;
	}

	return segments;
}
