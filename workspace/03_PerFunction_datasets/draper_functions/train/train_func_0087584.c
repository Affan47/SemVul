OTF_WBuffer_flush( OTF_WBuffer* wbuffer ) {


	int retval= 1;
	size_t ret;


	ret= OTF_File_write( wbuffer->file, wbuffer->buffer, wbuffer->pos );
	if( ret != wbuffer->pos ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"OTF_File_write() failed.\n",
				__FUNCTION__, __FILE__, __LINE__ );
		retval= 0;
	}

	wbuffer->pos= 0;

	return retval;
}
