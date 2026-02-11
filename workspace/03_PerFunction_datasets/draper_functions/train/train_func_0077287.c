SetCursorTextPos(unsigned int offset, unsigned int line) {
	my_allowHiddenCursor = false;
	if (line < 0) {
		SetCursorPos(0);
	} else if (line >= my_textdata.size()) {
		SetCursorPos(my_text.size());
		my_isCursorAtEOL = false;
	} else {
		PG_LineEdit::SetCursorPos(ConvertCursorPos(offset, line));
		my_isCursorAtEOL = (offset == my_textdata[line].size() && my_textdata[line].size() != 0);
		Update();
	}
}
