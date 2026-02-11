chopNotDigits(QString & string) {
	for (int ix = string.count() - 1; ix >= 0; ix--) {
        QChar ch = string.at(ix);
		if (ch.isDigit()) return;
        if (ch == '.') return;

		string.chop(1);
	}
}
