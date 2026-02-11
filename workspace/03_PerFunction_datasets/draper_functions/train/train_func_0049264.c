flmGetFileHdrInfo(
	FLMBYTE *		pPrefixBuf,
	FLMBYTE *		pFileHdrBuf,
	FILE_HDR *		pFileHdrRV)
{
	RCODE				rc = FERR_OK;
	FLMUINT			uiVersionNum;
	FLMUINT			uiTmpBlkSize;


	pFileHdrRV->uiBlockSize = (FLMUINT)FB2UW( &pFileHdrBuf [DB_BLOCK_SIZE]);
	pFileHdrRV->uiAppMajorVer = pPrefixBuf [10];
	pFileHdrRV->uiAppMinorVer = pPrefixBuf [11];
	pFileHdrRV->uiDefaultLanguage = pFileHdrBuf [DB_DEFAULT_LANGUAGE];
	pFileHdrRV->uiVersionNum = uiVersionNum =
		((FLMUINT16)(pFileHdrBuf [FLM_FILE_FORMAT_VER_POS] - ASCII_ZERO) * 100 +
		 (FLMUINT16)(pFileHdrBuf [FLM_MINOR_VER_POS] - ASCII_ZERO) * 10 +
		 (FLMUINT16)(pFileHdrBuf [FLM_SMINOR_VER_POS] - ASCII_ZERO));

	uiTmpBlkSize = pFileHdrRV->uiBlockSize;
	if( !VALID_BLOCK_SIZE( uiTmpBlkSize))
	{
		uiTmpBlkSize = flmAdjustBlkSize( pFileHdrRV->uiBlockSize);
	}


	pFileHdrRV->uiFirstLFHBlkAddr =
		(FLMUINT)FB2UD( &pFileHdrBuf [DB_1ST_LFH_ADDR]);


	if( (pPrefixBuf [1] != f_toascii('W')) ||
		 (pPrefixBuf [2] != f_toascii('P')) ||
		 (pPrefixBuf [3] != f_toascii('C')) ||
		 (!VALID_BLOCK_SIZE( pFileHdrRV->uiBlockSize)))
	{
		rc = RC_SET( FERR_NOT_FLAIM);
		goto Exit;
	}

	if( pFileHdrBuf [FLAIM_NAME_POS     ] != f_toascii( FLAIM_NAME[0]) ||
		 pFileHdrBuf [FLAIM_NAME_POS + 1 ] != f_toascii( FLAIM_NAME[1]) ||
		 pFileHdrBuf [FLAIM_NAME_POS + 2 ] != f_toascii( FLAIM_NAME[2]) ||
		 pFileHdrBuf [FLAIM_NAME_POS + 3 ] != f_toascii( FLAIM_NAME[3]) ||
		 pFileHdrBuf [FLAIM_NAME_POS + 4 ] != f_toascii( FLAIM_NAME[4]))
	{
		rc = RC_SET( FERR_NOT_FLAIM);
		goto Exit;
	}

	pFileHdrRV->uiSigBitsInBlkSize = flmGetSigBits( pFileHdrRV->uiBlockSize);


	if( RC_BAD( rc = flmCheckVersionNum( uiVersionNum)))
	{
		goto Exit;
	}

	f_memcpy( pFileHdrRV->ucFileHdr, pFileHdrBuf, FLM_FILE_HEADER_SIZE);

Exit:

	return( rc);
}
