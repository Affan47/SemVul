trimContinuationLine()
{
	size_t len = currentLine.length();
	size_t tabSize = getTabLength();
	charNum = 0;

	if (leadingSpaces > 0 && len > 0)
	{
		size_t i;
		size_t continuationIncrementIn = 0;
		for (i = 0; (i < len) && (i + continuationIncrementIn < leadingSpaces); i++)
		{
			if (!isWhiteSpace(currentLine[i]))
			{
				if (i < continuationIncrementIn)
					leadingSpaces = i + tabIncrementIn;
				continuationIncrementIn = tabIncrementIn;
				break;
			}
			if (currentLine[i] == '\t')
				continuationIncrementIn += tabSize - 1 - ((continuationIncrementIn + i) % tabSize);
		}

		if ((int) continuationIncrementIn == tabIncrementIn)
			charNum = i;
		else
		{

			string newLine;
			int leadingChars = 0;
			if ((int) leadingSpaces > tabIncrementIn)
				leadingChars = leadingSpaces - tabIncrementIn;
			newLine.append(leadingChars, ' ');
			newLine.append(currentLine, i, len - i);
			currentLine = newLine;
			charNum = leadingChars;
			if (currentLine.length() == 0)
				currentLine = string(" ");
		}
		if (i >= len)
			charNum = 0;
	}
	return;
}
