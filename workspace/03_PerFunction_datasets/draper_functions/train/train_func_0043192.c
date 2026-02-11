MovePositionTo(SelectionPosition newPos, Selection::selTypes selt, bool ensureVisible) {
	bool simpleCaret = (sel.Count() == 1) && sel.Empty();
	SelectionPosition spCaret = sel.Last();

	int delta = newPos.Position() - sel.MainCaret();
	newPos = ClampPositionIntoDocument(newPos);
	newPos = MovePositionOutsideChar(newPos, delta);
	if (!multipleSelection && sel.IsRectangular() && (selt == Selection::selStream)) {

		InvalidateSelection(SelectionRange(newPos), true);
		SelectionRange rangeMain = sel.RangeMain();
		sel.SetSelection(rangeMain);
	}
	if (!sel.IsRectangular() && (selt == Selection::selRectangle)) {

		SelectionRange rangeMain = sel.RangeMain();
		sel.Clear();
		sel.Rectangular() = rangeMain;
	}
	if (selt != Selection::noSel) {
		sel.selType = selt;
	}
	if (selt != Selection::noSel || sel.MoveExtends()) {
		SetSelection(newPos);
	} else {
		SetEmptySelection(newPos);
	}
	ShowCaretAtCurrentPosition();

	int currentLine = pdoc->LineFromPosition(newPos.Position());
	if (ensureVisible) {

		if (currentLine >= wrapPending.start)
			WrapLines(wsAll);
		XYScrollPosition newXY = XYScrollToMakeVisible(
			SelectionRange(posDrag.IsValid() ? posDrag : sel.RangeMain().caret), xysDefault);
		if (simpleCaret && (newXY.xOffset == xOffset)) {

			ScrollTo(newXY.topLine);
			InvalidateSelection(SelectionRange(spCaret), true);
		} else {
			SetXYScroll(newXY);
		}
	}

	if (highlightDelimiter.NeedsDrawing(currentLine)) {
		RedrawSelMargin();
	}
	return 0;
}
