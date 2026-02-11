updateFormattedLineSplitPointsOperator(const string &sequence)
{
	assert(maxCodeLength != string::npos);
	assert(formattedLine.length() > 0);

	if (!isOkToSplitFormattedLine())
		return;

	char nextChar = peekNextChar();


	if (nextChar == '/')
		return;


	if (sequence == "||" || sequence ==  "&&"|| sequence ==  "or"|| sequence ==  "and")
	{
		if (shouldBreakLineAfterLogical)
		{
			if (formattedLine.length() <= maxCodeLength)
				maxAndOr = formattedLine.length();
			else
				maxAndOrPending = formattedLine.length();
		}
		else
		{

			size_t sequenceLength = sequence.length();
			if (formattedLine.length() > sequenceLength
			        && isWhiteSpace(formattedLine[formattedLine.length() - sequenceLength - 1]))
				sequenceLength++;
			if (formattedLine.length() - sequenceLength <= maxCodeLength)
				maxAndOr = formattedLine.length() - sequenceLength;
			else
				maxAndOrPending = formattedLine.length() - sequenceLength;
		}
	}

	else if (sequence == "==" || sequence ==  "!=" || sequence ==  ">=" || sequence ==  "<=")
	{
		if (formattedLine.length() <= maxCodeLength)
			maxWhiteSpace = formattedLine.length();
		else
			maxWhiteSpacePending = formattedLine.length();
	}

	else if (sequence == "+" || sequence == "-" || sequence == "?")
	{
		if (charNum > 0
		        && (isLegalNameChar(currentLine[charNum - 1])
		            || currentLine[charNum - 1] == ')'
		            || currentLine[charNum - 1] == ']'
		            || currentLine[charNum - 1] == '\"'))
		{
			if (formattedLine.length() - 1 <=  maxCodeLength)
				maxWhiteSpace = formattedLine.length() - 1;
			else
				maxWhiteSpacePending = formattedLine.length() - 1;
		}
	}

	else if (sequence == "=")
	{

		size_t splitPoint = 0;
		if (formattedLine.length() <  maxCodeLength)
			splitPoint = formattedLine.length();
		else
			splitPoint = formattedLine.length() - 1;

		if (previousNonWSChar == ']')
		{
			if (formattedLine.length() - 1 <=  maxCodeLength)
				maxWhiteSpace = splitPoint;
			else
				maxWhiteSpacePending = splitPoint;
		}
		else if (charNum > 0
		         && (isLegalNameChar(currentLine[charNum - 1])
		             || currentLine[charNum - 1] == ')'
		             || currentLine[charNum - 1] == ']'))
		{
			if (formattedLine.length() <=  maxCodeLength)
				maxWhiteSpace = splitPoint;
			else
				maxWhiteSpacePending = splitPoint;
		}
	}
}
