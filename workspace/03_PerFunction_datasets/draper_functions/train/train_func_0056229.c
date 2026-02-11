textw(const char *text, unsigned int len) {
	XRectangle r;

	if(font.set) {
		XmbTextExtents(font.set, text, len, NULL, &r);
		return r.width;
	}
	return XTextWidth(font.xfont, text, len);
}
