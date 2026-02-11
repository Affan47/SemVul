bio_integrity_process(struct bio *bio,
				 integrity_processing_fn *proc_fn)
{
	struct blk_integrity *bi = bdev_get_integrity(bio->bi_bdev);
	struct blk_integrity_iter iter;
	struct bvec_iter bviter;
	struct bio_vec bv;
	struct bio_integrity_payload *bip = bio_integrity(bio);
	unsigned int ret = 0;
	void *prot_buf = page_address(bip->bip_vec->bv_page) +
		bip->bip_vec->bv_offset;

	iter.disk_name = bio->bi_bdev->bd_disk->disk_name;
	iter.interval = 1 << bi->interval_exp;
	iter.seed = bip_get_seed(bip);
	iter.prot_buf = prot_buf;

	bio_for_each_segment(bv, bio, bviter) {
		void *kaddr = kmap_atomic(bv.bv_page);

		iter.data_buf = kaddr + bv.bv_offset;
		iter.data_size = bv.bv_len;

		ret = proc_fn(&iter);
		if (ret) {
			kunmap_atomic(kaddr);
			return ret;
		}

		kunmap_atomic(kaddr);
	}
	return ret;
}
