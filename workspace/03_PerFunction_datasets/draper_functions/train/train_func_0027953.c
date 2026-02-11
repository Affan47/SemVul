patternSelected(int index) {
	Pattern* pattern = m_patterns.at(m_patterns_box->itemData(index).toInt());


	int count = m_word_count_box->currentText().toInt();
	m_word_count_box->clear();
	for (int i = pattern->minimumCount(); i <= 20; i += pattern->expandCount()) {
		m_word_count_box->addItem(QString::number(i));
	}
	setCount(count);


	int length = m_word_length_box->currentText().toInt();
	m_word_length_box->clear();
	for (int i = pattern->minimumLength(); i <= pattern->maximumLength(); ++i) {
		m_word_length_box->addItem(QString::number(i));
	}
	setLength(length);
}
