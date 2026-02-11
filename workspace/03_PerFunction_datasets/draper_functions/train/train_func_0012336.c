fill_buffer( proto *p, char *buf, int bufsize, int pos ) {
	while( pos < bufsize ) {
		int k = p->inf.do_stream_data(p->inf.custom,buf+pos,bufsize-pos);
		if( k <= 0 ) break;
		pos += k;
	}
	return pos;
}
