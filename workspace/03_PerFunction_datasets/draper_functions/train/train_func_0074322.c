appendMultilineRule(const QString& startPattern,
	const QString& endPattern, const QTextCharFormat& format,
	bool)
{
	mLastFormat = format;

	QRegExp srx=QRegExp(startPattern);
	QRegExp erx=QRegExp(endPattern);
	mMultiLineRule.startPattern = srx;
	mMultiLineRule.endPattern=erx;
	mMultiLineRule.format = format;
	mHighlightingMultilineRules.append(mMultiLineRule);
}
