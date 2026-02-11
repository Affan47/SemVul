isapnp_find_tag ( unsigned int wanted_tag, void *buf, size_t len ) {
	unsigned int tag;
	unsigned int tag_len;

	DBG2 ( "ISAPnP read tag" );
	do {
		tag = isapnp_peek_byte();
		if ( ISAPNP_IS_SMALL_TAG ( tag ) ) {
			tag_len = ISAPNP_SMALL_TAG_LEN ( tag );
			tag = ISAPNP_SMALL_TAG_NAME ( tag );
		} else {
			tag_len = ( isapnp_peek_byte() +
				    ( isapnp_peek_byte() << 8 ) );
			tag = ISAPNP_LARGE_TAG_NAME ( tag );
		}
		DBG2 ( " %02x (%02x)", tag, tag_len );
		if ( tag == wanted_tag ) {
			if ( len > tag_len )
				len = tag_len;
			isapnp_peek ( buf, len );
			DBG2 ( "\n" );
			return 0;
		} else {
			isapnp_peek ( NULL, tag_len );
		}
	} while ( tag != ISAPNP_TAG_END );
	DBG2 ( "\n" );
	return -ENOENT;
}
