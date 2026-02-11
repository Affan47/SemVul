SyOctalStrToInt64(const char *zSrc, sxu32 nLen, void * pOutVal, const char **zRest)
{
	const char *zIn, *zEnd;
	int isNeg = FALSE;
	sxi64 nVal = 0;
	int c;
#if defined(UNTRUST)
	if( SX_EMPTY_STR(zSrc) ){
		if( pOutVal ){
			*(sxi32 *)pOutVal = 0;
		}
		return SXERR_EMPTY;
	}
#endif
	zEnd = &zSrc[nLen];
	while(zSrc < zEnd && SyisSpace(zSrc[0]) ){
		zSrc++;
	}
	if( zSrc < zEnd && ( zSrc[0] == '-' || zSrc[0] == '+' ) ){
		isNeg = (zSrc[0] == '-') ? TRUE :FALSE;
		zSrc++;
	}

	while(zSrc < zEnd && zSrc[0] == '0' ){
		zSrc++;
	}
	zIn = zSrc;
	for(;;){
		if(zSrc >= zEnd || !SyisDigit(zSrc[0])){ break; } if( (c=zSrc[0]-'0') > 7 || (int)(zSrc-zIn) > 20){ break;} nVal = nVal * 8 +  c; zSrc++;
		if(zSrc >= zEnd || !SyisDigit(zSrc[0])){ break; } if( (c=zSrc[0]-'0') > 7 || (int)(zSrc-zIn) > 20){ break;} nVal = nVal * 8 +  c; zSrc++;
		if(zSrc >= zEnd || !SyisDigit(zSrc[0])){ break; } if( (c=zSrc[0]-'0') > 7 || (int)(zSrc-zIn) > 20){ break;} nVal = nVal * 8 +  c; zSrc++;
		if(zSrc >= zEnd || !SyisDigit(zSrc[0])){ break; } if( (c=zSrc[0]-'0') > 7 || (int)(zSrc-zIn) > 20){ break;} nVal = nVal * 8 +  c; zSrc++;
	}

	while(zSrc < zEnd && SyisSpace(zSrc[0])){
		zSrc++;
	}
	if( zRest ){
		*zRest = zSrc;
	}
	if( pOutVal ){
		if( isNeg == TRUE && nVal != 0 ){
			nVal = -nVal;
		}
		*(sxi64 *)pOutVal = nVal;
	}
	return (zSrc >= zEnd) ? SXRET_OK : SXERR_SYNTAX;
}
