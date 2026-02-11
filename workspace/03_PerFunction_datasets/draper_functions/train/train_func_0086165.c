GC_free(GC_PTR p)
# else
    void GC_free(p)
    GC_PTR p;
# endif
{
    register struct hblk *h;
    register hdr *hhdr;
    register signed_word sz;
    register ptr_t * flh;
    register int knd;
    register struct obj_kind * ok;
    DCL_LOCK_STATE;

    if (p == 0) return;

    h = HBLKPTR(p);
    hhdr = HDR(h);
    GC_ASSERT(GC_base(p) == p);
#   if defined(REDIRECT_MALLOC) && \
	(defined(GC_SOLARIS_THREADS) || defined(GC_LINUX_THREADS) \
	 || defined(__MINGW32__))


	if (0 == hhdr) return;
#   endif
    knd = hhdr -> hb_obj_kind;
    sz = hhdr -> hb_sz;
    ok = &GC_obj_kinds[knd];
    if (EXPECT((sz <= MAXOBJSZ), 1)) {
#	ifdef THREADS
	    DISABLE_SIGNALS();
	    LOCK();
#	endif
	GC_mem_freed += sz;


	if (IS_UNCOLLECTABLE(knd)) GC_non_gc_bytes -= WORDS_TO_BYTES(sz);


	if (ok -> ok_init) {
	    BZERO((word *)p + 1, WORDS_TO_BYTES(sz-1));
	}
	flh = &(ok -> ok_freelist[sz]);
	obj_link(p) = *flh;
	*flh = (ptr_t)p;
#	ifdef THREADS
	    UNLOCK();
	    ENABLE_SIGNALS();
#	endif
    } else {
    	DISABLE_SIGNALS();
        LOCK();
        GC_mem_freed += sz;
	if (IS_UNCOLLECTABLE(knd)) GC_non_gc_bytes -= WORDS_TO_BYTES(sz);
        GC_freehblk(h);
        UNLOCK();
        ENABLE_SIGNALS();
    }
}
