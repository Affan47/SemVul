draw_bigchar(imon_bigfont *font, int ch, int x, int y, PrivateData *p)
{
	imon_bigfont *defn = font;
	int i;
	int colBorder;

	while (defn->ch != ch && defn->ch != '\0') {
		defn++;
	}


	colBorder = 12;
	if (ch == ':')
		colBorder = 6;

	for (i = 0; i < colBorder; i++) {
		p->framebuf[x + i + (y * colBorder)] = (defn->pixels[i] & 0xFF00) >> 8;
	}
	for (i = 0; i < colBorder; i++) {
		p->framebuf[x + i + (y * colBorder) + p->bytesperline] = (defn->pixels[i] & 0x00FF);
	}
}
