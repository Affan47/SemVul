OTF_WStream_writeCollopSummaryKV( OTF_WStream* wstream,
		uint64_t time, uint32_t process, uint32_t comm, uint32_t collective,
		uint64_t number_sent, uint64_t number_recved, uint64_t bytes_sent,
		uint64_t bytes_recved, OTF_KeyValueList* list ) {


	OTF_WBuffer* buffer= OTF_WStream_getStatsBuffer( wstream );


	if ( NULL == buffer ) return 0;

	if ( 0 == OTF_WBuffer_setTimeAndProcess( buffer, time, process ) ) return 0;

	if ( OTF_WSTREAM_FORMAT_SHORT == ( wstream->format & 1 ) ) {

		OTF_WBuffer_writeKeyValueList_short(buffer, list);

		OTF_WBuffer_writeKeyword( buffer, OTF_KEYWORD_S_SUM_PREFIX
			OTF_KEYWORD_S_COLLOPMESSAGE );

		OTF_WBuffer_writeUint32( buffer, comm );
		OTF_WBuffer_writeKeyword( buffer, OTF_KEYWORD_S_LOCAL_COLLECTIVE );
		OTF_WBuffer_writeUint32( buffer, collective );
		OTF_WBuffer_writeKeyword( buffer, OTF_KEYWORD_S_LOCAL_NUMBERSENT );
		OTF_WBuffer_writeUint64( buffer, number_sent );
		OTF_WBuffer_writeKeyword( buffer, OTF_KEYWORD_S_LOCAL_NUMBERRECVD );
		OTF_WBuffer_writeUint64( buffer, number_recved );
		OTF_WBuffer_writeKeyword( buffer, OTF_KEYWORD_S_LOCAL_SENT );
		OTF_WBuffer_writeUint64( buffer, bytes_sent );
		OTF_WBuffer_writeKeyword( buffer, OTF_KEYWORD_S_LOCAL_RECVD );
		OTF_WBuffer_writeUint64( buffer, bytes_recved );

	} else if ( OTF_WSTREAM_FORMAT_LONG == ( wstream->format & 1 ) ) {

		OTF_WBuffer_writeKeyValueList_long(buffer, list);

		OTF_WBuffer_writeKeyword( buffer, OTF_KEYWORD_L_SUM_PREFIX
			OTF_KEYWORD_L_COLLOPMESSAGE " " );

		OTF_WBuffer_writeUint32( buffer, comm );
		OTF_WBuffer_writeKeyword( buffer, " " OTF_KEYWORD_L_LOCAL_COLLECTIVE " " );
		OTF_WBuffer_writeUint32( buffer, collective );
		OTF_WBuffer_writeKeyword( buffer, " " OTF_KEYWORD_L_LOCAL_NUMBERSENT " " );
		OTF_WBuffer_writeUint64( buffer, number_sent );
		OTF_WBuffer_writeKeyword( buffer, " " OTF_KEYWORD_L_LOCAL_NUMBERRECVD " " );
		OTF_WBuffer_writeUint64( buffer, number_recved );
		OTF_WBuffer_writeKeyword( buffer, " " OTF_KEYWORD_L_LOCAL_SENT " " );
		OTF_WBuffer_writeUint64( buffer, bytes_sent );
		OTF_WBuffer_writeKeyword( buffer, " " OTF_KEYWORD_L_LOCAL_RECVD " " );
		OTF_WBuffer_writeUint64( buffer, bytes_recved );
	}

	OTF_WBuffer_writeNewline( buffer );


	return ( OTF_NO_ERROR == otf_errno ) ? 1 : 0;
}
