linda_alloc_ctx ( struct linda *linda ) {
	unsigned int ctx;

	for ( ctx = 0 ; ctx < LINDA_NUM_CONTEXTS ; ctx++ ) {

		if ( ! linda->used_ctx[ctx] ) {
			linda->used_ctx[ctx ] = 1;
			DBGC2 ( linda, "Linda %p CTX %d allocated\n",
				linda, ctx );
			return ctx;
		}
	}

	DBGC ( linda, "Linda %p out of available contexts\n", linda );
	return -ENOENT;
}
