DelCharBack(bool allowLineStartDeletion) {
	if (!sel.IsRectangular())
		FilterSelections();
	if (sel.IsRectangular())
		allowLineStartDeletion = false;
	UndoGroup ug(pdoc, (sel.Count() > 1) || !sel.Empty());
	if (sel.Empty()) {
		for (size_t r=0; r<sel.Count(); r++) {
			if (!RangeContainsProtected(sel.Range(r).caret.Position() - 1, sel.Range(r).caret.Position())) {
				if (sel.Range(r).caret.VirtualSpace()) {
					sel.Range(r).caret.SetVirtualSpace(sel.Range(r).caret.VirtualSpace() - 1);
					sel.Range(r).anchor.SetVirtualSpace(sel.Range(r).caret.VirtualSpace());
				} else {
					int lineCurrentPos = pdoc->LineFromPosition(sel.Range(r).caret.Position());
					if (allowLineStartDeletion || (pdoc->LineStart(lineCurrentPos) != sel.Range(r).caret.Position())) {
						if (pdoc->GetColumn(sel.Range(r).caret.Position()) <= pdoc->GetLineIndentation(lineCurrentPos) &&
								pdoc->GetColumn(sel.Range(r).caret.Position()) > 0 && pdoc->backspaceUnindents) {
							UndoGroup ugInner(pdoc, !ug.Needed());
							int indentation = pdoc->GetLineIndentation(lineCurrentPos);
							int indentationStep = pdoc->IndentSize();
							if (indentation % indentationStep == 0) {
								pdoc->SetLineIndentation(lineCurrentPos, indentation - indentationStep);
							} else {
								pdoc->SetLineIndentation(lineCurrentPos, indentation - (indentation % indentationStep));
							}

							sel.Range(r) = SelectionRange(pdoc->GetLineIndentPosition(lineCurrentPos),
								pdoc->GetLineIndentPosition(lineCurrentPos));
						} else {
							pdoc->DelCharBack(sel.Range(r).caret.Position());
						}
					}
				}
			} else {
				sel.Range(r).ClearVirtualSpace();
			}
		}
		ThinRectangularRange();
	} else {
		ClearSelection();
	}
	sel.RemoveDuplicates();
	ContainerNeedsUpdate(SC_UPDATE_SELECTION);

	ShowCaretAtCurrentPosition();
}
