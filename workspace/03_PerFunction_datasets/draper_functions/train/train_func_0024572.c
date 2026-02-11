OTF_Reader_readFunctionSummary( OTF_RBuffer* buffer,
		OTF_HandlerArray* handlers ) {


	int ret= 1;

	uint32_t function;
	uint64_t count;
	uint64_t excltime;
	uint64_t incltime;


	if ( NULL == handlers->pointer[OTF_FUNCTIONSUMMARY_RECORD] ) {

		return OTF_RBuffer_readNewline( buffer );
	}


	function= OTF_RBuffer_readUint32( buffer );

	ret= ret && ( OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_S_LOCAL_COUNT )
			|| OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_L_LOCAL_COUNT )
			|| OTF_RBuffer_testKeyword( buffer, "C" ));
	count= OTF_RBuffer_readUint64( buffer );

	ret= ret && ( OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_S_LOCAL_EXCLTIME)
			|| OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_L_LOCAL_EXCLTIME) );
	excltime= OTF_RBuffer_readUint64( buffer );

	ret= ret && ( OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_S_LOCAL_INCLTIME)
			|| OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_L_LOCAL_INCLTIME) );
	incltime= OTF_RBuffer_readUint64( buffer );

	ret= ret && OTF_RBuffer_readNewline( buffer );

	if ( ret ) {


		return ( OTF_RETURN_OK  == ( (
			(OTF_Handler_FunctionSummary*)
			handlers->pointer[OTF_FUNCTIONSUMMARY_RECORD] )
			( handlers->firsthandlerarg[OTF_FUNCTIONSUMMARY_RECORD],
			buffer->time, function, buffer->process,
			count, excltime, incltime, buffer->list ) ) );
	} else {

		PARSE_ERROR( buffer );

		return 0;
	}
}
