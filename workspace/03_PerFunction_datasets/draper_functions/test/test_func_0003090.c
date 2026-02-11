ClearAll() {
	{
		UndoGroup ug(pdoc);
		if (0 != pdoc->Length()) {
			pdoc->DeleteChars(0, pdoc->Length());
		}
		if (!pdoc->IsReadOnly()) {
			cs.Clear();
			pdoc->AnnotationClearAll();
			pdoc->MarginClearAll();
		}
	}
	sel.Clear();
	SetTopLine(0);
	SetVerticalScrollPos();
	InvalidateStyleRedraw();
}
