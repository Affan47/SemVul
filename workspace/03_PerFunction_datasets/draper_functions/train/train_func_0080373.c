GC_reclaim_check(hbp, hhdr, sz)
register struct hblk *hbp;
register hdr * hhdr;
register word sz;
{
    register int word_no = 0;
    register word *p, *plim;
#   ifdef GATHERSTATS
        register int n_words_found = 0;
#   endif

    p = (word *)(hbp->hb_body);
    plim = (word *)((((word)hbp) + HBLKSIZE)
		   - WORDS_TO_BYTES(sz));


	while( p <= plim )  {
	    if( !mark_bit_from_hdr(hhdr, word_no) ) {
		FOUND_FREE(hbp, word_no);
	    }
	    p += sz;
	    word_no += sz;
	}
}
