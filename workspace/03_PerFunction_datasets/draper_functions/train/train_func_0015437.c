vcard_free( VCardFile *cardFile ) {
	cm_return_if_fail( cardFile != NULL );


	if( cardFile->file ) fclose( cardFile->file );


	addrcache_clear( cardFile->addressCache );
	addrcache_free( cardFile->addressCache );


	g_free( cardFile->path );


	cardFile->file = NULL;
	cardFile->path = NULL;
	cardFile->bufptr = NULL;

	cardFile->type = ADBOOKTYPE_NONE;
	cardFile->addressCache = NULL;
	cardFile->retVal = MGU_SUCCESS;


	g_free( cardFile );
}
