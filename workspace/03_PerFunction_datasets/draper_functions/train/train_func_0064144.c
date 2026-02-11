GC_add_ext_descriptor(bm, nbits)
GC_bitmap bm;
word nbits;
{
    register size_t nwords = divWORDSZ(nbits + WORDSZ-1);
    register signed_word result;
    register word i;
    register word last_part;
    register int extra_bits;
    DCL_LOCK_STATE;

    DISABLE_SIGNALS();
    LOCK();
    while (GC_avail_descr + nwords >= GC_ed_size) {
    	ext_descr * new;
    	size_t new_size;
    	word ed_size = GC_ed_size;

    	UNLOCK();
        ENABLE_SIGNALS();
    	if (ed_size == 0) {
    	    new_size = ED_INITIAL_SIZE;
    	} else {
    	    new_size = 2 * ed_size;
    	    if (new_size > MAX_ENV) return(-1);
    	}
    	new = (ext_descr *) GC_malloc_atomic(new_size * sizeof(ext_descr));
    	if (new == 0) return(-1);
    	DISABLE_SIGNALS();
        LOCK();
        if (ed_size == GC_ed_size) {
            if (GC_avail_descr != 0) {
    	        BCOPY(GC_ext_descriptors, new,
    	              GC_avail_descr * sizeof(ext_descr));
    	    }
    	    GC_ed_size = new_size;
    	    GC_ext_descriptors = new;
    	}
    }
    result = GC_avail_descr;
    for (i = 0; i < nwords-1; i++) {
        GC_ext_descriptors[result + i].ed_bitmap = bm[i];
        GC_ext_descriptors[result + i].ed_continued = TRUE;
    }
    last_part = bm[i];

    extra_bits = nwords * WORDSZ - nbits;
    last_part <<= extra_bits;
    last_part >>= extra_bits;
    GC_ext_descriptors[result + i].ed_bitmap = last_part;
    GC_ext_descriptors[result + i].ed_continued = FALSE;
    GC_avail_descr += nwords;
    UNLOCK();
    ENABLE_SIGNALS();
    return(result);
}
