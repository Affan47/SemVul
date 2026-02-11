OTF_File_write( OTF_File* file, const void* ptr, size_t size ) {


	size_t byteswritten = 0;

#ifdef HAVE_ZLIB
	int status;
#endif


	if ( NULL != file->externalbuffer ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
			"not yet supported in 'external buffer' mode.\n",
			__FUNCTION__, __FILE__, __LINE__ );
		return (size_t) -1;
	}


	if( OTF_FILEMODE_WRITE != file->mode ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"current file->mode is not OTF_FILEMODE_WRITE. writing forbidden.\n",
				__FUNCTION__, __FILE__, __LINE__ );

		return 0;
	}


	if( 0 == OTF_File_revive( file, OTF_FILEMODE_WRITE ) ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"OTF_File_revive() failed.\n",
				__FUNCTION__, __FILE__, __LINE__ );

		return 0;
	}

#ifdef HAVE_ZLIB

	if ( NULL != file->z ) {


		OTF_FILE_Z(file)->avail_in = size;
		OTF_FILE_Z(file)->next_in = (void*)ptr;

		while (OTF_FILE_Z(file)->avail_in > 0) {

			status = deflate(OTF_FILE_Z(file), Z_FULL_FLUSH);
			if (status == Z_STREAM_ERROR) {

				OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
						"error in compressing, status %i.\n",
						__FUNCTION__, __FILE__, __LINE__, status );
				return byteswritten;
			}

			while (OTF_FILE_Z(file)->avail_out == 0) {

				size_t towrite = file->zbuffersize - OTF_FILE_Z(file)->avail_out;
				if (towrite != OTF_File_write_internal(file, file->zbuffer, towrite)) {

					OTF_Error( "ERROR in function %s, file: %s, line %i:\n",
							"Failed to write %u bytes to file!\n",
							__FUNCTION__, __FILE__, __LINE__, towrite);
					return byteswritten;
				}
				OTF_FILE_Z(file)->avail_out = file->zbuffersize;
				OTF_FILE_Z(file)->next_out = file->zbuffer;
				status = deflate(OTF_FILE_Z(file), Z_FULL_FLUSH);
				if (status == Z_STREAM_ERROR) {

					OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
							"error in compressing, status %i.\n",
							__FUNCTION__, __FILE__, __LINE__, status );
					assert(status != Z_STREAM_ERROR);
					return byteswritten;
				}
			}
			byteswritten = size - OTF_FILE_Z(file)->avail_in;
		}
	} else {

#endif

		byteswritten= OTF_File_write_internal(file, ptr, size);
		if( byteswritten < size ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"less bytes written than expected %u < %u.\n",
					__FUNCTION__, __FILE__, __LINE__, (uint32_t) byteswritten,
					(uint32_t) size );

		}


#ifdef HAVE_ZLIB
	}
#endif
    return byteswritten;

}
