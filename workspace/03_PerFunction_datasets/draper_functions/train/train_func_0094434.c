OTF_RBuffer_jump( OTF_RBuffer* rbuffer, uint64_t filepos ) {


	int ret;
	size_t read;

	uint32_t i;

	ret= OTF_File_seek( rbuffer->file, filepos );

	if ( 0 != ret ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"OTF_File_seek() failed.\n",
				__FUNCTION__, __FILE__, __LINE__ );

		return 0;
	}

	rbuffer->pos= 0;
	read= OTF_File_read( rbuffer->file, rbuffer->buffer, rbuffer->jumpsize );

	rbuffer->end= (uint32_t) read;

	i= rbuffer->end;
	rbuffer->lastnewline= 0;

	while ( i > 0 ) {

		--i;

		if ( '\n' == rbuffer->buffer[i] ) {

			rbuffer->lastnewline= i;
			break;
		}
	}


	if ( 0 == OTF_RBuffer_guaranteeRecord( rbuffer ) ) {


		return 0;
	}


	if ( 0 != filepos ) {


		OTF_RBuffer_readNewline( rbuffer );
	}


	if ( 0 == OTF_RBuffer_guaranteeRecord( rbuffer ) ) {


		return 0;
	}


	rbuffer->time= (uint64_t) -1;
	rbuffer->process= (uint32_t) -1;


	while ( ((uint64_t) -1) == rbuffer->time ) {


		if ( 0 == OTF_RBuffer_guaranteeRecord( rbuffer ) ) {


			return 0;
		}

		if ( OTF_RBuffer_checkTimeRecord( rbuffer ) ) {

			continue;
		}


		OTF_RBuffer_readNewline( rbuffer );
	}


	while ( ((uint32_t) -1) == rbuffer->process ) {


		if ( 0 == OTF_RBuffer_guaranteeRecord( rbuffer ) ) {


			return 0;
		}

		if ( OTF_RBuffer_checkProcessRecord( rbuffer ) ) {

			continue;
		}


		OTF_RBuffer_readNewline( rbuffer );
	}

	return 1;
}
