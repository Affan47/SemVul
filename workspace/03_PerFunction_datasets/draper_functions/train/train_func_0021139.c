isDereferenceOrAddressOf() const
{
	assert(currentChar == '*' || currentChar == '&' || currentChar == '^');

	if (isCharImmediatelyPostTemplate)
		return false;

	if (previousNonWSChar == '='
	        || previousNonWSChar == ','
	        || previousNonWSChar == '.'
	        || previousNonWSChar == '{'
	        || previousNonWSChar == '>'
	        || previousNonWSChar == '<'
	        || isCharImmediatelyPostLineComment
	        || isCharImmediatelyPostComment
	        || isCharImmediatelyPostReturn)
		return true;


	if (currentChar == '*'
	        && (int) currentLine.length() > charNum
	        && currentLine[charNum+1] == '*')
	{
		if (previousNonWSChar == '(')
			return true;
		if ((int) currentLine.length() < charNum + 2)
			return true;
		return false;
	}


	if (charNum == (int) currentLine.find_first_not_of(" \t"))
		return true;

	char nextChar = peekNextChar();
	if (nextChar == ')' || nextChar == '>' || nextChar == ',')
		return false;


	if (( currentChar == '*' && nextChar == '&')
	        || (previousNonWSChar == '*' && currentChar == '&'))
		return false;

	if (!isBracketType(bracketTypeStack->back(), COMMAND_TYPE)
	        && parenStack->back() == 0)
		return false;

	string lastWord = getPreviousWord(currentLine, charNum);
	if (lastWord == "else" || lastWord == "delete")
		return true;

	bool isDA = (!(isLegalNameChar(previousNonWSChar) || previousNonWSChar == '>')
	             || (!isLegalNameChar(nextChar) && nextChar != '/')
	             || (ispunct((unsigned char)previousNonWSChar) && previousNonWSChar != '.')
	             || isCharImmediatelyPostReturn);

	return isDA;
}
