OTF_RStream_getEventBuffer( OTF_RStream* rstream ) {


	char* filename;


	if ( NULL == rstream->eventBuffer ) {

		filename = OTF_getFilename( rstream->namestub,
			rstream->id, OTF_FILETYPE_EVENT, 0, NULL );
		if( NULL == filename ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"OTF_getFilename() failed for event file with name stub '%s' and ID %u.\n",
					__FUNCTION__, __FILE__, __LINE__, rstream->namestub, rstream->id );

			return NULL;
		}

		rstream->eventBuffer= OTF_RBuffer_open( filename, rstream->manager );
		free( filename );
		filename = NULL;

		if ( NULL == rstream->eventBuffer ) {


			return NULL;
		}

		OTF_RBuffer_setSize( rstream->eventBuffer, rstream->buffersizes );
#ifdef HAVE_ZLIB
		OTF_RBuffer_setZBufferSize( rstream->eventBuffer, rstream->zbuffersizes );
#endif
	}

	return rstream->eventBuffer;
}
