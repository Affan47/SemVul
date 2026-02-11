countPermutations(const QString& word) {
	Q_ASSERT(!word.isEmpty());

	int n = factorial(word.length());
	int d = 1;

	QString sorted = word;
	std::sort(sorted.begin(), sorted.end());
	QChar c;
	int count = 0;
	foreach (const QChar& c2, sorted) {
		if (c2 != c) {
			c = c2;
			d *= factorial(count);
			count = 1;
		} else {
			count++;
		}
	}
	d *= factorial(count);

	return n / d;
}
