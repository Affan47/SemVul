OTF_RBuffer_readUint32( OTF_RBuffer* rbuffer ) {


	char c;
	uint32_t ret = 0;


	OTF_RBuffer_skipSpaces( rbuffer );

	while( 1 ) {

		c= rbuffer->buffer[rbuffer->pos];

		if ( '0' <= c && c <= '9' ) {

			ret = (ret << 4) | ( c - '0' );
			++(rbuffer->pos);

		} else if ( 'a' <= c && c <= 'f' ) {

			ret = (ret << 4) | ( c - ( 'a' - 10 ) );
			++(rbuffer->pos);

		} else {

			return ret;
		}
	}
}
