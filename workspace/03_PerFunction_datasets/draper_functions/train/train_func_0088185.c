OTF_File_open_with_external_buffer( uint32_t len, const char* buffer,
        uint8_t is_compressed, OTF_FileMode mode ) {

	OTF_File* ret;

	ret= (OTF_File*) malloc( sizeof(OTF_File) );
	if( NULL == ret ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"no memory left.\n",
				__FUNCTION__, __FILE__, __LINE__ );

		return NULL;
	}

	OTF_File_init( ret );

	ret->externalbuffer= buffer;
	ret->externalpos= 0;
	ret->externallen= (uint64_t) len;

	ret->mode = mode;

	if ( is_compressed ) {

#ifdef HAVE_ZLIB


		ret->z= malloc( sizeof(z_stream) );
		if( NULL == ret->z ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					  "no memory left.\n",
					  __FUNCTION__, __FILE__, __LINE__ );

			free( ret );
			ret= NULL;

			return NULL;
		}

		OTF_FILE_Z(ret)->next_in= NULL;
		OTF_FILE_Z(ret)->avail_in= 0;
		OTF_FILE_Z(ret)->zalloc= NULL;
		OTF_FILE_Z(ret)->zfree= NULL;
		OTF_FILE_Z(ret)->opaque= NULL;

		inflateInit( OTF_FILE_Z(ret) );

		ret->zbuffer= malloc( ret->zbuffersize );
		if( NULL == ret->zbuffer ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"no memory left.\n",
					__FUNCTION__, __FILE__, __LINE__ );

			free( ret->zbuffer );
			ret->zbuffer= NULL;
			free( ret->z );
			ret->z= NULL;
			free( ret );
			ret= NULL;

			return NULL;
		}

#else

		free( ret );
		ret= NULL;

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"built without HAVE_ZLIB, still trying to open with compressed buffer.\n",
				__FUNCTION__, __FILE__, __LINE__ );

		return NULL;

#endif

	} else {


	}

	ret->manager= NULL;

	return ret;
}
