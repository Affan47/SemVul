matchBrackets()
{

	QList<QTextEdit::ExtraSelection> extraSelections;
	if (!isReadOnly())
	{
		QTextEdit::ExtraSelection selection;
		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}
	setExtraSelections(extraSelections);


	m_matchingBegin = -1;
	m_matchingEnd = -1;
	if (!m_showMatchingBrackets) return;

	m_plainText = toPlainText();

	const QString matchText = m_plainText;
	const QTextCursor cursor = textCursor();
	int pos = cursor.position();
	if (pos == -1)
		return;
	else if (cursor.atEnd() || !QString("({[]})").contains(m_plainText.at(pos)))
	{
		if (pos <= 0 || !QString("({[]})").contains(m_plainText.at(--pos)))
			return;
	}


	QChar car = (!cursor.atEnd()) ? matchText.at(pos) : matchText.at(pos - 1);
	QChar matchCar;
	long inc = 1;
	if (car == '(') matchCar = ')';
	else if (car == '{') matchCar = '}';
	else if (car == '[') matchCar = ']';
	else
	{
		inc = -1;
		if (car == ')') matchCar = '(';
		else if (car == '}') matchCar = '{';
		else if (car == ']') matchCar = '[';
		else
			return;
	}


	m_matchingBegin = pos;
	int numOfMatchCharsToSkip = 0;
	do
	{
		if (matchText.at(pos) == car)
			numOfMatchCharsToSkip++;
		else if (matchText.at(pos) == matchCar)
		{
			numOfMatchCharsToSkip--;
			if (numOfMatchCharsToSkip == 0)
			{
				m_matchingEnd = pos;
				break;
			}
		}
		pos += inc;
	}
	while (pos >= 0 && pos < matchText.length());

	if (m_matchingBegin > m_matchingEnd)
		qSwap(m_matchingBegin, m_matchingEnd);


	if (m_matchingBegin != -1)
		showMatchingBrackets();
}
