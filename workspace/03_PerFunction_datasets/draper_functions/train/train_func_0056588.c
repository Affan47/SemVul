CreateFromArray(BYTE* pArray,DWORD dwWidth,DWORD dwHeight,DWORD dwBitsperpixel, DWORD dwBytesperline, bool bFlipImage)
{
	if (pArray==NULL) return false;
	if (!((dwBitsperpixel==1)||(dwBitsperpixel==4)||(dwBitsperpixel==8)||
		(dwBitsperpixel==24)||(dwBitsperpixel==32))) return false;

	if (!Create(dwWidth,dwHeight,dwBitsperpixel)) return false;

	if (dwBitsperpixel<24) SetGrayPalette();

#if CXIMAGE_SUPPORT_ALPHA
	if (dwBitsperpixel==32) AlphaCreate();
#endif

	BYTE *dst,*src;

	for (DWORD y = 0; y<dwHeight; y++) {
		dst = info.pImage + (bFlipImage?(dwHeight-1-y):y) * info.dwEffWidth;
		src = pArray + y * dwBytesperline;
		if (dwBitsperpixel==32){
			for(DWORD x=0;x<dwWidth;x++){
				*dst++=src[0];
				*dst++=src[1];
				*dst++=src[2];
#if CXIMAGE_SUPPORT_ALPHA
				AlphaSet(x,(bFlipImage?(dwHeight-1-y):y),src[3]);
#endif
				src+=4;
			}
		} else {
			memcpy(dst,src,min(info.dwEffWidth,dwBytesperline));
		}
	}
	return true;
}
