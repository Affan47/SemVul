iCheckOS2 (const OS2_HEAD * CONST_RESTRICT Header)
{
	if ((Header->bfType != ('B'|('M'<<8))) || (Header->DataOff < 26) || (Header->cbFix < 12))
		return IL_FALSE;
	if (Header->cPlanes != 1)
		return IL_FALSE;
	if (Header->cx == 0 || Header->cy == 0)
		return IL_FALSE;
	if (Header->cBitCount != 1 && Header->cBitCount != 4 && Header->cBitCount != 8 &&
		 Header->cBitCount != 24)
		 return IL_FALSE;

	return IL_TRUE;
}
