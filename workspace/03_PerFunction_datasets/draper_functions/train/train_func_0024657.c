AutoCompleteInsert(Position startPos, int removeLen, const char *text, int textLen) {
	UndoGroup ug(pdoc);
	pdoc->DeleteChars(startPos, removeLen);
	pdoc->InsertString(startPos, text, textLen);
	SetEmptySelection(startPos + textLen);
}
