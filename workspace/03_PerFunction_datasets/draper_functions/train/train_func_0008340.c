do_hash( MD_HANDLE md, MD_HANDLE md2, IOBUF fp, int textmode )
{
    text_filter_context_t tfx;
    int c;

    if( textmode ) {
	memset( &tfx, 0, sizeof tfx);
	iobuf_push_filter( fp, text_filter, &tfx );
    }
    if( md2 ) {

	int lc = -1;
	while( (c = iobuf_get(fp)) != -1 ) {
	    if( c == '\n' && lc == '\r' )
		md_putc(md2, c);
	    else if( c == '\n' ) {
		md_putc(md2, '\r');
		md_putc(md2, c);
	    }
	    else if( c != '\n' && lc == '\r' ) {
		md_putc(md2, '\n');
		md_putc(md2, c);
	    }
	    else
		md_putc(md2, c);

	    if( md )
		md_putc(md, c );
	    lc = c;
	}
    }
    else {
	while( (c = iobuf_get(fp)) != -1 ) {
	    if( md )
		md_putc(md, c );
	}
    }
}
