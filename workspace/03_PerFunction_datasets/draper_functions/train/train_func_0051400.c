SyUriEncode(const char *zSrc, sxu32 nLen, ProcConsumer xConsumer, void *pUserData)
{
	unsigned char *zIn = (unsigned char *)zSrc;
	unsigned char zHex[3] = { '%', 0, 0 };
	unsigned char zOut[2];
	unsigned char *zCur, *zEnd;
	sxi32 c;
	sxi32 rc;
#ifdef UNTRUST
	if( SX_EMPTY_STR(zSrc) || xConsumer == 0 ){
		return SXERR_EMPTY;
	}
#endif
	rc = SXRET_OK;
	zEnd = &zIn[nLen]; zCur = zIn;
	for(;;){
		if( zCur >= zEnd ){
			if( zCur != zIn ){
				rc = xConsumer(zIn, (sxu32)(zCur-zIn), pUserData);
			}
			break;
		}
		c = zCur[0];
		if( SAFE_HTTP(c) ){
			zCur++; continue;
		}
		if( zCur != zIn && SXRET_OK != (rc = xConsumer(zIn, (sxu32)(zCur-zIn), pUserData))){
			break;
		}
		if( c == ' ' ){
			zOut[0] = '+';
			rc = xConsumer((const void *)zOut, sizeof(unsigned char), pUserData);
		}else{
			zHex[1]	= "0123456789ABCDEF"[(c >> 4) & 0x0F];
			zHex[2] = "0123456789ABCDEF"[c & 0x0F];
			rc = xConsumer(zHex, sizeof(zHex), pUserData);
		}
		if( SXRET_OK != rc ){
			break;
		}
		zIn = &zCur[1]; zCur = zIn ;
	}
	return rc == SXRET_OK ? SXRET_OK : SXERR_ABORT;
}
