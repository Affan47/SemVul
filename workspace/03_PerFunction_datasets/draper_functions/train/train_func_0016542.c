OTF_WStream_finish( OTF_WStream* wstream ) {


	int ret= 1;
#	ifdef OTF_DEBUG
		int tmpret;
#	endif

	free( wstream->namestub );
	wstream->namestub= NULL;

	wstream->id= (uint32_t) -1;


	if ( NULL != wstream->defBuffer ) {

#		ifndef OTF_DEBUG
			ret&= OTF_WBuffer_close( wstream->defBuffer );
#		else
			tmpret= OTF_WBuffer_close( wstream->defBuffer );
			if( 0 == tmpret ) {
				OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"OTF_WBuffer_close() failed for the def buffer.\n",
					__FUNCTION__, __FILE__, __LINE__ );
			}
			ret&= tmpret;
#		endif

		wstream->defBuffer= NULL;
	}

	if ( NULL != wstream->eventBuffer ) {

#		ifndef OTF_DEBUG
			ret&= OTF_WBuffer_close( wstream->eventBuffer );
#		else
			tmpret= OTF_WBuffer_close( wstream->eventBuffer );
			if( 0 == tmpret ) {
				OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"OTF_WBuffer_close() failed for the event buffer.\n",
					__FUNCTION__, __FILE__, __LINE__ );
			}
			ret&= tmpret;
#		endif

		wstream->eventBuffer= NULL;
	}

	if ( NULL != wstream->snapsBuffer ) {

#		ifndef OTF_DEBUG
			ret&= OTF_WBuffer_close( wstream->snapsBuffer );
#		else
			tmpret= OTF_WBuffer_close( wstream->snapsBuffer );
			if( 0 == tmpret ) {
				OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"OTF_WBuffer_close() failed for the snapshots buffer.\n",
					__FUNCTION__, __FILE__, __LINE__ );
			}
			ret&= tmpret;
#		endif

		wstream->snapsBuffer= NULL;
	}

	if ( NULL != wstream->statsBuffer ) {

#		ifndef OTF_DEBUG
			ret&= OTF_WBuffer_close( wstream->statsBuffer );
#		else
			tmpret= OTF_WBuffer_close( wstream->statsBuffer );
			if( 0 == tmpret ) {
				OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"OTF_WBuffer_close() failed for the statistics buffer.\n",
					__FUNCTION__, __FILE__, __LINE__ );
			}
			ret&= tmpret;
#		endif

		wstream->statsBuffer= NULL;
	}

	if ( NULL != wstream->markerBuffer ) {

#		ifndef OTF_DEBUG
			ret&= OTF_WBuffer_close( wstream->markerBuffer );
#		else
			tmpret= OTF_WBuffer_close( wstream->markerBuffer );
			if( 0 == tmpret ) {
				OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"OTF_WBuffer_close() failed for the statistics buffer.\n",
					__FUNCTION__, __FILE__, __LINE__ );
			}
			ret&= tmpret;
#		endif

		wstream->markerBuffer= NULL;
	}

	return ret;
}
