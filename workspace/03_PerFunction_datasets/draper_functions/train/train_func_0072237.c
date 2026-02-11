replaceAll(const QString &text, const QString &replacement,
    bool isCaseSensitive, bool findWholeWords, bool forward, bool startAtCursor)
{
	while (search(text, isCaseSensitive, findWholeWords, forward, startAtCursor))
	{
		replace(replacement);
		emit setSearchFromBegin(false);
	}
	emit setSearchFromBegin(true);
}
