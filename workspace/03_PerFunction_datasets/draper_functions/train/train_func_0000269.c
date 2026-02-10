OTF_File_size( OTF_File* file ) {


	struct stat st;

	if ( NULL != file->iofsl ) {
		return OTF_File_iofsl_size( file );
	}

	if ( NULL != file->externalbuffer ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
			"not yet supported in 'external buffer' mode.\n",
			__FUNCTION__, __FILE__, __LINE__ );
		return (uint64_t) -1;
	}


	if ( stat( file->filename, &st ) == -1 ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"stat() failed: %s\n",
				__FUNCTION__, __FILE__, __LINE__,
				strerror(errno) );

		return 0;
	} else {

		return st.st_size;

	}
}
