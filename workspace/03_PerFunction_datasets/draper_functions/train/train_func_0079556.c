gb18030_encode( unsigned int unicode, unsigned char out[4] )
{
	int len;
	if ( unicode < 0x80 ) {
		out[0] = unicode;
		len = 1;
	} else {
		len = gb18030_unicode_table_lookup( unicode, out );
		if ( !len )
			len = gb18030_unicode_range_lookup( unicode, out );
	}
	return len;
}
