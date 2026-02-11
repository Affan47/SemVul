NeedWrapping(int docLineStart, int docLineEnd) {

	if (wrapPending.AddRange(docLineStart, docLineEnd)) {
		llc.Invalidate(LineLayout::llPositions);
	}

	if ((wrapState != eWrapNone) && wrapPending.NeedsWrap()) {
		SetIdle(true);
	}
}
