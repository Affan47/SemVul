ColouriseDiffDoc(unsigned int startPos, int length, int, WordList *[], Accessor &styler) {
	char lineBuffer[1024];
	styler.StartAt(startPos);
	styler.StartSegment(startPos);
	unsigned int linePos = 0;
	for (unsigned int i = startPos; i < startPos + length; i++) {
		lineBuffer[linePos++] = styler[i];
		if (AtEOL(styler, i) || (linePos >= sizeof(lineBuffer) - 1)) {

			lineBuffer[linePos] = '\0';
			ColouriseDiffLine(lineBuffer, i, styler);
			linePos = 0;
		}
	}
	if (linePos > 0) {
		ColouriseDiffLine(lineBuffer, startPos + length - 1, styler);
	}
}
