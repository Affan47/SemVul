InLine(int offset, int line) const {
	return ((offset >= LineStart(line)) && (offset < LineStart(line + 1))) ||
		((offset == numCharsInLine) && (line == (lines-1)));
}
