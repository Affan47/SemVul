appendText(QTextDocument *doc, QTextCursor &cursor, const QString &text)
{
	cursor.beginEditBlock();
	cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
	cursor.clearSelection();
	if (!cursor.atBlockStart()) {
		cursor.insertBlock();


		QTextBlockFormat blockFormat = cursor.blockFormat();
		blockFormat.clearProperty(QTextFormat::BlockTrailingHorizontalRulerWidth);
		cursor.setBlockFormat(blockFormat);
	}

	appendTextHelper(doc, text, cursor);

	cursor.endEditBlock();
}
