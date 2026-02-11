LocationFromPosition(SelectionPosition pos) {
	Point pt;
	RefreshStyleData();
	if (pos.Position() == INVALID_POSITION)
		return pt;
	int line = pdoc->LineFromPosition(pos.Position());
	int lineVisible = cs.DisplayFromDoc(line);

	AutoSurface surface(this);
	AutoLineLayout ll(llc, RetrieveLineLayout(line));
	if (surface && ll) {

		pt.y = (lineVisible - topLine - 1) * vs.lineHeight;
		pt.x = 0;
		unsigned int posLineStart = pdoc->LineStart(line);
		LayoutLine(line, surface, vs, ll, wrapWidth);
		int posInLine = pos.Position() - posLineStart;

		if (posInLine > ll->maxLineLength) {
			pt.x = ll->positions[ll->maxLineLength] - ll->positions[ll->LineStart(ll->lines)];
		}

		for (int subLine = 0; subLine < ll->lines; subLine++) {
			if ((posInLine >= ll->LineStart(subLine)) && (posInLine <= ll->LineStart(subLine + 1))) {
				pt.x = ll->positions[posInLine] - ll->positions[ll->LineStart(subLine)];
				if (ll->wrapIndent != 0) {
					int lineStart = ll->LineStart(subLine);
					if (lineStart != 0)
						pt.x += ll->wrapIndent;
				}
			}
			if (posInLine >= ll->LineStart(subLine)) {
				pt.y += vs.lineHeight;
			}
		}
		pt.x += vs.fixedColumnWidth - xOffset;
	}
	pt.x += pos.VirtualSpace() * static_cast<int>(vs.styles[ll->EndLineStyle()].spaceWidth);
	return pt;
}
