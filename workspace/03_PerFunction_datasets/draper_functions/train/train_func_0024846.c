FillRun(Surface *surface, int code, int startX, int y, int x) {
	if ((code != codeTransparent) && (startX != x)) {
		PRectangle rc(startX, y, x, y+1);
		surface->FillRectangle(rc, ColourFromCode(code));
	}
}
