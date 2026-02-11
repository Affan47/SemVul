DelCharBack(int pos) {
	if (pos <= 0) {
		return;
	} else if (IsCrLf(pos - 2)) {
		DeleteChars(pos - 2, 2);
	} else if (dbcsCodePage) {
		int startChar = NextPosition(pos, -1);
		DeleteChars(startChar, pos - startChar);
	} else {
		DeleteChars(pos - 1, 1);
	}
}
