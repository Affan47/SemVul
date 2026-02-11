LineSelection(int lineCurrentPos_, int lineAnchorPos_, bool wholeLine) {
	int selCurrentPos, selAnchorPos;
	if (wholeLine) {
		int lineCurrent_ = pdoc->LineFromPosition(lineCurrentPos_);
		int lineAnchor_ = pdoc->LineFromPosition(lineAnchorPos_);
		if (lineAnchorPos_ < lineCurrentPos_) {
			selCurrentPos = pdoc->LineStart(lineCurrent_ + 1);
			selAnchorPos = pdoc->LineStart(lineAnchor_);
		} else if (lineAnchorPos_ > lineCurrentPos_) {
			selCurrentPos = pdoc->LineStart(lineCurrent_);
			selAnchorPos = pdoc->LineStart(lineAnchor_ + 1);
		} else {
			selCurrentPos = pdoc->LineStart(lineAnchor_ + 1);
			selAnchorPos = pdoc->LineStart(lineAnchor_);
		}
	} else {
		if (lineAnchorPos_ < lineCurrentPos_) {
			selCurrentPos = StartEndDisplayLine(lineCurrentPos_, false) + 1;
			selCurrentPos = pdoc->MovePositionOutsideChar(selCurrentPos, 1);
			selAnchorPos = StartEndDisplayLine(lineAnchorPos_, true);
		} else if (lineAnchorPos_ > lineCurrentPos_) {
			selCurrentPos = StartEndDisplayLine(lineCurrentPos_, true);
			selAnchorPos = StartEndDisplayLine(lineAnchorPos_, false) + 1;
			selAnchorPos = pdoc->MovePositionOutsideChar(selAnchorPos, 1);
		} else {
			selCurrentPos = StartEndDisplayLine(lineAnchorPos_, false) + 1;
			selCurrentPos = pdoc->MovePositionOutsideChar(selCurrentPos, 1);
			selAnchorPos = StartEndDisplayLine(lineAnchorPos_, true);
		}
	}
	TrimAndSetSelection(selCurrentPos, selAnchorPos);
}
