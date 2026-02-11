decreaseIndent()
{
	m_current_document->setRichText(true);
	QTextCursor cursor = m_current_document->text()->textCursor();
	QTextBlockFormat format = cursor.blockFormat();
	format.setIndent(qMax(0, format.indent() - 48));
	cursor.setBlockFormat(format);
	emit updateFormatActions();
}
