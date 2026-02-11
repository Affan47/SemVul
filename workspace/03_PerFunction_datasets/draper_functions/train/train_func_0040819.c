OTF_WStream_writeNoOpKV( OTF_WStream* wstream, uint64_t time,
    uint32_t process, OTF_KeyValueList* list ) {


	OTF_WBuffer* buffer= OTF_WStream_getEventBuffer( wstream );


	if ( NULL == buffer ) return 0;

	if ( 0 == OTF_WBuffer_setTimeAndProcess( buffer, time, process ) ) return 0;

	if ( OTF_WSTREAM_FORMAT_SHORT == ( wstream->format & 1 ) ) {

		OTF_WBuffer_writeKeyValueList_short(buffer, list);

		OTF_WBuffer_writeKeyword( buffer,
			OTF_KEYWORD_S_NOOP );

		OTF_WBuffer_writeNewline( buffer );

	} else if ( OTF_WSTREAM_FORMAT_LONG == ( wstream->format & 1 ) ) {

		OTF_WBuffer_writeKeyValueList_long(buffer, list);

		OTF_WBuffer_writeKeyword( buffer,
			OTF_KEYWORD_L_NOOP " " );

		OTF_WBuffer_writeNewline( buffer );
	}


	return ( OTF_NO_ERROR == otf_errno ) ? 1 : 0;
}
