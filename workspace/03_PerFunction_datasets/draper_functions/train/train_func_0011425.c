documentRemoved(Document* document)
{
	Deltas* delta = m_deltas.take(document);
	m_character_count += delta->characterCount();
	m_character_and_space_count += delta->characterAndSpaceCount();
	m_page_count += delta->pageCount();
	m_paragraph_count += delta->paragraphCount();
	m_word_count += delta->wordCount();
	delete delta;
}
