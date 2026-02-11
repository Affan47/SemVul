Clear() {

	if (sel.Empty()) {
		bool singleVirtual = false;
		if ((sel.Count() == 1) &&
			!RangeContainsProtected(sel.MainCaret(), sel.MainCaret() + 1) &&
			sel.RangeMain().Start().VirtualSpace()) {
			singleVirtual = true;
		}
		UndoGroup ug(pdoc, (sel.Count() > 1) || singleVirtual);
		for (size_t r=0; r<sel.Count(); r++) {
			if (!RangeContainsProtected(sel.Range(r).caret.Position(), sel.Range(r).caret.Position() + 1)) {
				if (sel.Range(r).Start().VirtualSpace()) {
					if (sel.Range(r).anchor < sel.Range(r).caret)
						sel.Range(r) = SelectionPosition(InsertSpace(sel.Range(r).anchor.Position(), sel.Range(r).anchor.VirtualSpace()));
					else
						sel.Range(r) = SelectionPosition(InsertSpace(sel.Range(r).caret.Position(), sel.Range(r).caret.VirtualSpace()));
				}
				if ((sel.Count() == 1) || !pdoc->IsPositionInLineEnd(sel.Range(r).caret.Position())) {
					pdoc->DelChar(sel.Range(r).caret.Position());
					sel.Range(r).ClearVirtualSpace();
				}
			} else {
				sel.Range(r).ClearVirtualSpace();
			}
		}
	} else {
		ClearSelection();
	}
	sel.RemoveDuplicates();
}
