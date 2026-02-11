setCursorPosition(int row, int col)
{
	const int pos = getCursorPosition(row, col);
	QTextCursor cursor = textCursor();
	cursor.setPosition(pos, QTextCursor::MoveAnchor);
	setTextCursor(cursor);


	centerCursor();
	setFocus();
}
