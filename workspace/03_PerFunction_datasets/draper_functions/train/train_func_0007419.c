blkif_setup_rw_req_grant(unsigned long gfn, unsigned int offset,
				     unsigned int len, void *data)
{
	struct setup_rw_req *setup = data;
	int n, ref;
	struct grant *gnt_list_entry;
	unsigned int fsect, lsect;

	unsigned int grant_idx = setup->grant_idx;
	struct blkif_request *ring_req = setup->ring_req;
	struct blkfront_info *info = setup->info;
	struct blk_shadow *shadow = &info->shadow[setup->id];

	if ((ring_req->operation == BLKIF_OP_INDIRECT) &&
	    (grant_idx % GRANTS_PER_INDIRECT_FRAME == 0)) {
		if (setup->segments)
			kunmap_atomic(setup->segments);

		n = grant_idx / GRANTS_PER_INDIRECT_FRAME;
		gnt_list_entry = get_indirect_grant(&setup->gref_head, info);
		shadow->indirect_grants[n] = gnt_list_entry;
		setup->segments = kmap_atomic(gnt_list_entry->page);
		ring_req->u.indirect.indirect_grefs[n] = gnt_list_entry->gref;
	}

	gnt_list_entry = get_grant(&setup->gref_head, gfn, info);
	ref = gnt_list_entry->gref;
	shadow->grants_used[grant_idx] = gnt_list_entry;

	if (setup->need_copy) {
		void *shared_data;

		shared_data = kmap_atomic(gnt_list_entry->page);


		memcpy(shared_data + offset,
		       setup->bvec_data + setup->bvec_off,
		       len);

		kunmap_atomic(shared_data);
		setup->bvec_off += len;
	}

	fsect = offset >> 9;
	lsect = fsect + (len >> 9) - 1;
	if (ring_req->operation != BLKIF_OP_INDIRECT) {
		ring_req->u.rw.seg[grant_idx] =
			(struct blkif_request_segment) {
				.gref       = ref,
				.first_sect = fsect,
				.last_sect  = lsect };
	} else {
		setup->segments[grant_idx % GRANTS_PER_INDIRECT_FRAME] =
			(struct blkif_request_segment) {
				.gref       = ref,
				.first_sect = fsect,
				.last_sect  = lsect };
	}

	(setup->grant_idx)++;
}
