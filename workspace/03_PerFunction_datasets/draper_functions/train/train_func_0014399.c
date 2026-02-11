CheckAndCorrectColormap(TIFF* tif, int n, uint16* r, uint16* g, uint16* b)
{
	int i;

	for (i = 0; i < n; i++)
		if (r[i] >= 256 || g[i] >= 256 || b[i] >= 256)
			return;
	TIFFWarning(TIFFFileName(tif), "Scaling 8-bit colormap");
#define	CVT(x)		(((x) * ((1L<<16)-1)) / 255)
	for (i = 0; i < n; i++) {
		r[i] = CVT(r[i]);
		g[i] = CVT(g[i]);
		b[i] = CVT(b[i]);
	}
#undef CVT
}
