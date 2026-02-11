ddp_tag_reserve(struct cxgbi_sock *csk, unsigned int tid,
			   u32 sw_tag, u32 *tagp, struct cxgbi_gather_list *gl,
			   gfp_t gfp)
{
	struct cxgbi_device *cdev = csk->cdev;
	struct cxgbi_ddp_info *ddp = cdev->ddp;
	struct cxgbi_tag_format *tformat = &cdev->tag_format;
	struct cxgbi_pagepod_hdr hdr;
	unsigned int npods;
	int idx = -1;
	int err = -ENOMEM;
	u32 tag;

	npods = (gl->nelem + PPOD_PAGES_MAX - 1) >> PPOD_PAGES_SHIFT;
	if (ddp->idx_last == ddp->nppods)
		idx = ddp_find_unused_entries(ddp, 0, ddp->nppods,
							npods, gl);
	else {
		idx = ddp_find_unused_entries(ddp, ddp->idx_last + 1,
							ddp->nppods, npods,
							gl);
		if (idx < 0 && ddp->idx_last >= npods) {
			idx = ddp_find_unused_entries(ddp, 0,
				min(ddp->idx_last + npods, ddp->nppods),
							npods, gl);
		}
	}
	if (idx < 0) {
		log_debug(1 << CXGBI_DBG_DDP,
			"xferlen %u, gl %u, npods %u NO DDP.\n",
			gl->length, gl->nelem, npods);
		return idx;
	}

	tag = cxgbi_ddp_tag_base(tformat, sw_tag);
	tag |= idx << PPOD_IDX_SHIFT;

	hdr.rsvd = 0;
	hdr.vld_tid = htonl(PPOD_VALID_FLAG | PPOD_TID(tid));
	hdr.pgsz_tag_clr = htonl(tag & ddp->rsvd_tag_mask);
	hdr.max_offset = htonl(gl->length);
	hdr.page_offset = htonl(gl->offset);

	err = cdev->csk_ddp_set(csk, &hdr, idx, npods, gl);
	if (err < 0)
		goto unmark_entries;

	ddp->idx_last = idx;
	log_debug(1 << CXGBI_DBG_DDP,
		"xfer %u, gl %u,%u, tid 0x%x, tag 0x%x->0x%x(%u,%u).\n",
		gl->length, gl->nelem, gl->offset, tid, sw_tag, tag, idx,
		npods);
	*tagp = tag;
	return 0;

unmark_entries:
	ddp_unmark_entries(ddp, idx, npods);
	return err;
}
