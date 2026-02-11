OTF_RStream_finish( OTF_RStream* rstream ) {


	int ret=1;
	int tmpret;

	free( rstream->namestub );
	rstream->namestub= NULL;

	rstream->id= (uint32_t) -1;

	if ( NULL != rstream->defBuffer ) {

		tmpret= OTF_RBuffer_close( rstream->defBuffer );
		ret &= tmpret;
		if( 0 == tmpret ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"cannot close defbuffer.\n",
					__FUNCTION__, __FILE__, __LINE__ );
		}
		rstream->defBuffer= NULL;
	}

	if ( NULL != rstream->eventBuffer ) {

		tmpret= OTF_RBuffer_close( rstream->eventBuffer );
		ret &= tmpret;
		if( 0 == tmpret ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"cannot close event buffer.\n",
					__FUNCTION__, __FILE__, __LINE__ );

		}
		rstream->eventBuffer= NULL;
	}

	if ( NULL != rstream->snapsBuffer ) {

		tmpret= OTF_RBuffer_close( rstream->snapsBuffer );
		ret &= tmpret;
		if( 0 == tmpret ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"cannot close snapshots buffer.\n",
					__FUNCTION__, __FILE__, __LINE__ );

		}
		rstream->snapsBuffer= NULL;
	}

	if ( NULL != rstream->statsBuffer ) {

		tmpret= OTF_RBuffer_close( rstream->statsBuffer );
		ret &= tmpret;
		if( 0 == tmpret ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"cannot close statistics buffer.\n",
					__FUNCTION__, __FILE__, __LINE__ );

		}
		rstream->statsBuffer= NULL;
	}

	if ( NULL != rstream->markerBuffer ) {

		tmpret= OTF_RBuffer_close( rstream->markerBuffer );
		ret &= tmpret;
		if( 0 == tmpret ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"cannot close defbuffer.\n",
					__FUNCTION__, __FILE__, __LINE__ );

		}
		rstream->markerBuffer= NULL;
	}

	return ret;
}
