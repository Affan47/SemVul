suggestion(QAction* action)
{
	if (action == m_add_action) {
		m_text->setTextCursor(m_start_cursor);
		m_dictionary.addWord(m_word);
	} else if (action == m_check_action) {
		m_text->setTextCursor(m_start_cursor);
		SpellChecker::checkDocument(m_text, m_dictionary);
	} else {
		m_cursor.insertText(action->text());
	}
}
