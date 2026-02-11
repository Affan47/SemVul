OTF_WBuffer_writeUint64( OTF_WBuffer* wbuffer, uint64_t value ) {


	static char dig[16] = {	'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	uint32_t l= 0;
	int s= 60;
	uint32_t v= 0;
	char* p = NULL;


	if( 0 == OTF_WBuffer_guarantee( wbuffer, 16 ) ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"OTF_WBuffer_guarantee() failed.\n",
				__FUNCTION__, __FILE__, __LINE__  );

		return 0;
	}


	p= wbuffer->buffer + wbuffer->pos;


	while ( ( 0 == v ) && ( s >= 0 ) ) {

		v= (uint32_t) (( value >> s ) & 0xf) ;
		s -= 4;
	}

	p[l++]= dig[v];

	while ( s >= 0 ) {

		v= (uint32_t) (( value >> s ) & 0xf) ;
		s -= 4;

		p[l++]= dig[v];
	}

	wbuffer->pos += l;

	return l;
}
