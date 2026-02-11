next_unallocated_cb(local_cache_buffer_t *lb, off64_t bnum)
{
    cbindex_t *next;

    if( !have_unused_buf(lb)) {

	emit_debug( "caught attempt to allocate too many cbindex objects");
	return NULL;
    }

    next = &lb->cbi [lb->nbcache];
    next->bpo = malloc(lb->buflen);

    if( next->bpo == NULL) {
	emit_debug( "out-of-memory allocating index-%d cbindex object",
		    lb->nbcache);
	return NULL;
    }

    lb->nbcache++;
    next->nused = 0;
    next->bnum = bnum;

    emit_debug( "allocating next buffer %llu %lu ",
		bnum, lb->nbcache);

    return next;
}
