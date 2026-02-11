OTF_RBuffer_testPrefix( OTF_RBuffer* rbuffer, const char* string ) {


	uint32_t i = 0;
	uint32_t j = rbuffer->pos;


	OTF_RBuffer_skipSpaces( rbuffer );


	while ( string[i] )	{

		if ( string[i] != rbuffer->buffer[j] ) {

			return 0;

		} else {

			++i;
			++j;
		}
	}

	rbuffer->pos = j;

	return 1;
}
