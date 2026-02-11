Create(DWORD dwWidth, DWORD dwHeight, DWORD wBpp, DWORD imagetype)
{

	if (!Destroy())
		return NULL;


	if ((dwWidth == 0) || (dwHeight == 0)){
		strcpy(info.szLastError,"CxImage::Create : width and height must be greater than zero");
		return NULL;
	}


    if		(wBpp <= 1)	wBpp = 1;
    else if (wBpp <= 4)	wBpp = 4;
    else if (wBpp <= 8)	wBpp = 8;
    else				wBpp = 24;


	if (((dwWidth*dwHeight*wBpp)>>3) > CXIMAGE_MAX_MEMORY ||
		((dwWidth*dwHeight*wBpp)/wBpp) != (dwWidth*dwHeight))
	{
		strcpy(info.szLastError,"CXIMAGE_MAX_MEMORY exceeded");
		return NULL;
	}


    switch (wBpp){
        case 1:
            head.biClrUsed = 2;	break;
        case 4:
            head.biClrUsed = 16; break;
        case 8:
            head.biClrUsed = 256; break;
        default:
            head.biClrUsed = 0;
    }


    info.dwEffWidth = ((((wBpp * dwWidth) + 31) / 32) * 4);
    info.dwType = imagetype;


	head.biSize = sizeof(BITMAPINFOHEADER);
    head.biWidth = dwWidth;
    head.biHeight = dwHeight;
    head.biPlanes = 1;
    head.biBitCount = (WORD)wBpp;
    head.biCompression = BI_RGB;
    head.biSizeImage = info.dwEffWidth * dwHeight;


	pDib = malloc(GetSize());
    if (!pDib){
		strcpy(info.szLastError,"CxImage::Create can't allocate memory");
		return NULL;
	}


	RGBQUAD* pal=GetPalette();
	if (pal) memset(pal,0,GetPaletteSize());

#if CXIMAGE_SUPPORT_SELECTION
	if (pSelection) SelectionDelete();
#endif

#if CXIMAGE_SUPPORT_ALPHA
	if (pAlpha) AlphaDelete();
#endif


    BITMAPINFOHEADER*  lpbi;
	lpbi = (BITMAPINFOHEADER*)(pDib);
    *lpbi = head;

	info.pImage=GetBits();

    return pDib;
}
