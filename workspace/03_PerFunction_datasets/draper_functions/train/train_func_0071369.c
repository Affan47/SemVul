addRandomWord(Qt::Orientation orientation) {

	QString filter;
	QPoint pos = m_current;
	QPoint delta = (orientation == Qt::Horizontal) ? QPoint(1, 0) : QPoint(0, 1);
	for (int i = 0; i <= wordLength(); ++i) {
		QChar c = at(pos);
		filter.append(c.isNull() ? QChar('.') : c);
		pos += delta;
	}
	QStringList filtered = m_words.value(wordLength()).filter(QRegExp(filter));


	QStringList words;
	QString sorted;
	bool anagram;
	foreach (const QString& word, filtered) {
		anagram = false;
		sorted = word;
		std::sort(sorted.begin(), sorted.end());
		foreach (const QString& skip, m_skip) {
			if (sorted == skip) {
				anagram = true;
				break;
			}
		}
		if (!anagram) {
			words.append(word);
		}
	}


	QString result = !words.isEmpty() ? words.at(qrand() % words.count()) : QString();
	if (result.isEmpty()) {
		return 0;
	}
	Word* word = new Word(result, m_current, orientation);
	std::sort(result.begin(), result.end());
	m_skip.append(result);
	return word;
}
