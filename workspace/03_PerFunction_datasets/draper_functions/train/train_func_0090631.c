IndentAmount(int line, int *flags, PFNIsCommentLeader pfnIsCommentLeader) {
	int end = Length();
	int spaceFlags = 0;


	int pos = LineStart(line);
	char ch = (*this)[pos];
	int indent = 0;
	bool inPrevPrefix = line > 0;
	int posPrev = inPrevPrefix ? LineStart(line-1) : 0;
	while ((ch == ' ' || ch == '\t') && (pos < end)) {
		if (inPrevPrefix) {
			char chPrev = (*this)[posPrev++];
			if (chPrev == ' ' || chPrev == '\t') {
				if (chPrev != ch)
					spaceFlags |= wsInconsistent;
			} else {
				inPrevPrefix = false;
			}
		}
		if (ch == ' ') {
			spaceFlags |= wsSpace;
			indent++;
		} else {
			spaceFlags |= wsTab;
			if (spaceFlags & wsSpace)
				spaceFlags |= wsSpaceTab;
			indent = (indent / 8 + 1) * 8;
		}
		ch = (*this)[++pos];
	}

	*flags = spaceFlags;
	indent += SC_FOLDLEVELBASE;

	if ((ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') ||
	        (pfnIsCommentLeader && (*pfnIsCommentLeader)(*this, pos, end-pos)))
		return indent | SC_FOLDLEVELWHITEFLAG;
	else
		return indent;
}
