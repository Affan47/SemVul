Xmgr_24Zpolyline(unsigned char *buf, float *zbuf, int zwidth, int width, int height,
		 CPoint3 *p, int n, int lwidth, int *color)
{
    int i;
    CPoint3 *cp;

    if (n == 1)
    {
	setZpixel(buf, zbuf, zwidth, width, height, p, color);
	return;
    }

    for (i=0, cp=p; i<n-1; i++)
	if (cp->drawnext)
	    Xmgr_24Zline(buf, zbuf, zwidth, width, height, cp, cp+1,
			 lwidth, color);
}
