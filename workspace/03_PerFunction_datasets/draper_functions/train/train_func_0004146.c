OTF_RBuffer_checkTimeRecord( OTF_RBuffer* rbuffer ) {


	uint32_t p;
	char c;


	p= rbuffer->pos;
	c= rbuffer->buffer[ p ];
	while ( ( ' ' == c ) || ( '\t' == c ) ) {

		++p;
		c= rbuffer->buffer[ p ];
	}


	if ( ( '0' <= c && c <= '9' ) || ( 'a' <= c && c <= 'f' ) ) {


		rbuffer->pos= p;
		rbuffer->time= OTF_RBuffer_readUint64( rbuffer );
		OTF_RBuffer_readNewline( rbuffer );
		return 1;
	}


	return 0;
}
