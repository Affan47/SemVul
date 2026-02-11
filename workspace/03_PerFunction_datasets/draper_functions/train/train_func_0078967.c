GC_reclaim_small_nonempty_block(hbp, report_if_found COUNT_PARAM)
register struct hblk *hbp;
int report_if_found;
COUNT_DECL
{
    hdr *hhdr = HDR(hbp);
    word sz = hhdr -> hb_sz;
    int kind = hhdr -> hb_obj_kind;
    struct obj_kind * ok = &GC_obj_kinds[kind];
    ptr_t * flh = &(ok -> ok_freelist[sz]);

    hhdr -> hb_last_reclaimed = (unsigned short) GC_gc_no;

    if (report_if_found) {
	GC_reclaim_check(hbp, hhdr, sz);
    } else {
        *flh = GC_reclaim_generic(hbp, hhdr, sz,
				  (ok -> ok_init || GC_debugging_started),
	 			  *flh MEM_FOUND_ADDR);
    }
}
