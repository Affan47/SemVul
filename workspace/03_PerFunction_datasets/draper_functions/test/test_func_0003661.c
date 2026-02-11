GetColorType()
{
	BYTE b = (BYTE)((head.biBitCount>8) ? 2  : 1 );
#if CXIMAGE_SUPPORT_ALPHA
	if (AlphaIsValid()) b = 4 ;
#endif
	return b;
}
