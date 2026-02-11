gdImageStringUp(gdImagePtr im, gdFontPtr f, int x, int y, char *s, int color)
{
	int i;
	int l;
	l = strlen(s);
	for (i=0; (i<l); i++) {
		gdImageCharUp(im, f, x, y, s[i], color);
		y -= f->w;
	}
}
