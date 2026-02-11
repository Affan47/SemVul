FoldPODoc(unsigned int startPos, int length, int, WordList *[], Accessor &styler) {
	if (! styler.GetPropertyInt("fold"))
		return;
	bool foldCompact = styler.GetPropertyInt("fold.compact") != 0;
	bool foldComment = styler.GetPropertyInt("fold.comment") != 0;

	unsigned int endPos = startPos + length;
	int curLine = styler.GetLine(startPos);
	int lineState = styler.GetLineState(curLine);
	int nextLineState;
	int level = styler.LevelAt(curLine) & SC_FOLDLEVELNUMBERMASK;
	int nextLevel;
	int visible = 0;
	int chNext = styler[startPos];

	for (unsigned int i = startPos; i < endPos; i++) {
		int ch = chNext;
		chNext = styler.SafeGetCharAt(i+1);

		if (! isspacechar(ch)) {
			visible++;
		} else if ((ch == '\r' && chNext != '\n') || ch == '\n' || i+1 >= endPos) {
			int lvl = level;
			int nextLine = curLine + 1;

			nextLineState = styler.GetLineState(nextLine);
			if ((lineState != SCE_PO_COMMENT || foldComment) &&
					nextLineState == lineState &&
					FindNextNonEmptyLineState(i, styler) == lineState)
				nextLevel = SC_FOLDLEVELBASE + 1;
			else
				nextLevel = SC_FOLDLEVELBASE;

			if (nextLevel > level)
				lvl |= SC_FOLDLEVELHEADERFLAG;
			if (visible == 0 && foldCompact)
				lvl |= SC_FOLDLEVELWHITEFLAG;

			styler.SetLevel(curLine, lvl);

			lineState = nextLineState;
			curLine = nextLine;
			level = nextLevel;
			visible = 0;
		}
	}
}
