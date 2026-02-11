addWord(int step) {
	Word* result = 0;
	switch (step) {
		case 0:
			result = addRandomWord(Qt::Horizontal);
			break;
		case 1:
			result = addRandomWord(Qt::Vertical);
			m_current += QPoint(0, wordLength());
			break;
		case 2:
			result = addRandomWord(Qt::Horizontal);
			m_current += QPoint(wordLength(), -wordLength());
			break;
		case 3:
			result = addRandomWord(Qt::Vertical);
			m_current = QPoint(m_current.x() - 2, m_current.y() ? 0 : (wordLength() - 2));
			break;
		default:
			break;
	}
	return result;
}
