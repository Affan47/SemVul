nd_blk_rw_integrity(struct nd_blk_device *blk_dev,
				struct bio_integrity_payload *bip, u64 lba,
				int rw)
{
	unsigned int len = nd_blk_meta_size(blk_dev);
	resource_size_t	dev_offset, ns_offset;
	struct nd_namespace_blk *nsblk;
	struct nd_blk_region *ndbr;
	int err = 0;

	nsblk = blk_dev->nsblk;
	ndbr = blk_dev->ndbr;
	ns_offset = lba * blk_dev->internal_lbasize + blk_dev->sector_size;
	dev_offset = to_dev_offset(nsblk, ns_offset, len);
	if (dev_offset == SIZE_MAX)
		return -EIO;

	while (len) {
		unsigned int cur_len;
		struct bio_vec bv;
		void *iobuf;

		bv = bvec_iter_bvec(bip->bip_vec, bip->bip_iter);


		cur_len = min(len, bv.bv_len);
		iobuf = kmap_atomic(bv.bv_page);
		err = ndbr->do_io(ndbr, dev_offset, iobuf + bv.bv_offset,
				cur_len, rw);
		kunmap_atomic(iobuf);
		if (err)
			return err;

		len -= cur_len;
		dev_offset += cur_len;
		bvec_iter_advance(bip->bip_vec, &bip->bip_iter, cur_len);
	}

	return err;
}
