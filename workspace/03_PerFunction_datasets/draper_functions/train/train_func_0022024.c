do_stream_data( void *_c, char *buf, int size ) {
	mcontext *c = (mcontext*)_c;

	if( size == 0 ) {
		if( !ap_should_client_block(c->r) )
			return -1;
		c->need_discard = true;
		return 0;
	}
	return ap_get_client_block(c->r,buf,size);
}
