fritzboxRegister( unsigned nMaxB3Connection, unsigned nMaxB3Blks, unsigned nMaxSizeB3, unsigned *pnApplId ) {
	unsigned char anMessage[ 256 ];
	unsigned char *pnPtr = anMessage;
	int nSock, nError;


	*pnApplId = -1;


	nSock = fritzboxOpenSocket();
	if ( nSock < 0 ) {
		return nSock;
	}


	fritzboxSetHeader( &pnPtr, 20, 0x0000, CAPICMD( 0x20, CAPI_REQ ) );


	put_byte( &pnPtr, 0x09 );


	put_byte( &pnPtr, 0x00 );
	put_byte( &pnPtr, 0x00 );

	put_byte( &pnPtr, 0x06 );

	put_word( &pnPtr, nMaxB3Connection );

	put_word( &pnPtr, nMaxB3Blks );

	put_word( &pnPtr, nMaxSizeB3 );


	if ( !( fritzboxRemoteCommand( nSock, anMessage, 23 ) ) ) {

		CapiDebug( 1, "Error: Unable to register CAPI! (ApplId: %d, MaxB3Con: %d, MaxB3Blks: %d, MaxB3Size: %d)\n", *pnApplId, nMaxB3Connection, nMaxB3Blks, nMaxSizeB3 );
		close( nSock );
		return -2;
	}

	nError = CAPIMSG_U16( anMessage, 16 );
	if ( nError != 0 ) {
		CapiDebug( 1, "Error: Unable to register CAPI! Error %x\n", nError );
		close( nSock );
		return -3;
	}


	*pnApplId = CAPIMSG_APPID( anMessage );
	CapiDebug( 1, "Successfully registered CAPI (ApplId: %d, MaxB3Con: %d, MaxB3Blks: %d, MaxB3Size: %d)\n", *pnApplId, nMaxB3Connection, nMaxB3Blks, nMaxSizeB3 );

	return nSock;
}
