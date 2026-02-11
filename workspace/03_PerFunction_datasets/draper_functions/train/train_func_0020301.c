removeFontFamilySingleQuotes(QString &fileContent) {
	static QString pattern = "font-family=\"('[^']*')\"";
	QSet<QString> wrongFontFamilies = TextUtils::getRegexpCaptures(pattern, fileContent);

	foreach(QString ff, wrongFontFamilies) {
		QString wrongFF = ff;
		QString fixedFF = ff.remove('\'');
		fileContent.replace(wrongFF,fixedFF);
	}

	return wrongFontFamilies.size() > 0;
}
