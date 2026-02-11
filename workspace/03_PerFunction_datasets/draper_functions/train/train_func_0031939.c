isPointerOrReference() const
{
	assert(currentChar == '*' || currentChar == '&' || currentChar == '^');

	if (isJavaStyle())
		return false;

	if ((currentChar == '&' && previousChar == '&')
	        || isCharImmediatelyPostOperator)
		return false;

	if (previousNonWSChar == '='
	        || previousNonWSChar == '('
	        || previousNonWSChar == '['
	        || isCharImmediatelyPostReturn
	        || isInTemplate
	        || isCharImmediatelyPostTemplate
	        || currentHeader == &AS_CATCH)
		return true;


	string lastWord = getPreviousWord(currentLine, charNum);
	if (lastWord.empty())
		lastWord = " ";
	char nextChar = peekNextChar();


	if (isDigit(lastWord[0])
	        || isDigit(nextChar)
	        || nextChar == '!')
		return false;

	if (isBracketType(bracketTypeStack->back(), ARRAY_TYPE)
	        && isLegalNameChar(lastWord[0])
	        && isLegalNameChar(nextChar)
	        && previousNonWSChar != ')')
	{
		if (isArrayOperator())
			return false;
	}


	if (parenStack->back() > 0
	        && isLegalNameChar(lastWord[0])
	        && isLegalNameChar(nextChar))
	{

		const string* followingOperator = getFollowingOperator();
		if (followingOperator
		        && followingOperator != &AS_MULT
		        && followingOperator != &AS_BIT_AND)
		{
			if (followingOperator == &AS_ASSIGN)
				return true;
			else
				return false;
		}

		if (!isBracketType(bracketTypeStack->back(), COMMAND_TYPE))
			return true;
		else
			return false;
	}


	if (parenStack->back() > 0
	        && nextChar == '('
	        && previousNonWSChar != ','
	        && previousNonWSChar != '('
	        && previousNonWSChar != '!'
	        && previousNonWSChar != '&'
	        && previousNonWSChar != '*'
	        && previousNonWSChar != '|')
		return false;

	if (nextChar == '-'
	        || nextChar == '+')
	{
		size_t nextNum = currentLine.find_first_not_of(" \t", charNum + 1);
		if (nextNum != string::npos)
		{
			if (currentLine.compare(nextNum, 2, "++") != 0
			        && currentLine.compare(nextNum, 2, "--") != 0)
				return false;
		}
	}

	bool isPR = (!isInPotentialCalculation
	             || isBracketType(bracketTypeStack->back(), DEFINITION_TYPE)
	             || (!isLegalNameChar(previousNonWSChar)
	                 && !(previousNonWSChar == ')' && nextChar == '(')
	                 && !(previousNonWSChar == ')' && currentChar == '*' && !isImmediatelyPostCast())
	                 && previousNonWSChar != ']')
	            );

	if (!isPR)
	{
		isPR |= (!isWhiteSpace(nextChar)
		         && nextChar != '-'
		         && nextChar != '('
		         && nextChar != '['
		         && !isLegalNameChar(nextChar));
	}

	return isPR;
}
