SetPalette(DWORD n, BYTE *r, BYTE *g, BYTE *b)
{
	if ((!r)||(pDib==NULL)||(head.biClrUsed==0)) return;
	if (!g) g = r;
	if (!b) b = g;
	RGBQUAD* ppal=GetPalette();
	DWORD m=min(n,head.biClrUsed);
	for (DWORD i=0; i<m;i++){
		ppal[i].rgbRed=r[i];
		ppal[i].rgbGreen=g[i];
		ppal[i].rgbBlue=b[i];
	}
	info.last_c_isvalid = false;
}
