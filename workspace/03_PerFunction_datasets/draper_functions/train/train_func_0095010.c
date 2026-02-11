rcapiGetSerialNumber( int nHandle, unsigned nController, unsigned char *pnBuffer ) {
	unsigned char anBuf[ 100 ];
	unsigned char *pnPtr = anBuf;

	rcapiSetHeader( &pnPtr, 14, RCAPI_GET_SERIAL_NUMBER_REQ, nController );
	if ( !( rcapiRemoteCommand( nHandle, anBuf, 14, RCAPI_GET_SERIAL_NUMBER_CONF ) ) ) {
		return 0;
	}

	memcpy( pnBuffer, anBuf + 1, CAPI_SERIAL_LEN );
	pnBuffer[ CAPI_SERIAL_LEN - 1 ] = 0;

	return pnBuffer;
}
