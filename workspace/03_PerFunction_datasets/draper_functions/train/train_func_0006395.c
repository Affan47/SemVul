cursor_pput(uint dx)
{
	uint vx = 0, px = 0;
	char line[1024];
	char *linep=line;

	uint linelen;
	if (!textfile->getline(top_line+cursory, 0, line, sizeof line, &linelen, NULL)) return;

	while (linelen--) {
		if (px==dx) break;
		int k = char_vsize(*(linep++), vx);
		vx += k;
		px++;
	}
	vx += dx-px;
	if (xofs > vx) {
		cursorx = 0;
		xofs = vx;
	} else {
		cursorx = vx-xofs;
		if (cursorx > (uint)size.w-1) {
			xofs += cursorx-(size.w-1);
			cursorx = size.w-1;
		}
	}
}
