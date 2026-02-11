sceneSelected(const QModelIndex& index)
{
	if (!m_document || !scenesVisible()) {
		return;
	}

	if (index.isValid()) {
		int block_number = index.data(Qt::UserRole).toInt();
		QTextBlock block = m_document->text()->document()->findBlockByNumber(block_number);
		QTextCursor cursor = m_document->text()->textCursor();
		cursor.setPosition(block.position());
		m_document->text()->setTextCursor(cursor);
		m_document->centerCursor(true);
	}
}
