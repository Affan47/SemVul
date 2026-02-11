OTF_Writer_writeDefProcessGroupKV( OTF_Writer* writer, uint32_t streamid,
		uint32_t deftoken, const char* name, uint32_t n,
		const uint32_t* array, OTF_KeyValueList *list ) {


	OTF_WStream* stream= OTF_Writer_getStream( writer, (uint32_t) streamid );

	if ( 0 == writer->defHeaderWritten ) {

		OTF_Writer_writeDefinitionHeader( writer );
		writer->defHeaderWritten= 1;
	}

	return OTF_WStream_writeDefProcessGroupKV( stream, deftoken,
		name, n, (uint32_t*) array, list );
}
