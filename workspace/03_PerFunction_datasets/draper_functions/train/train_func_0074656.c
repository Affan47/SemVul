processSwitchBlock(string &line, size_t index)
{
	size_t i = index;
	bool isPotentialKeyword = isCharPotentialHeader(line, i);

	if (line[i] == '{')
	{
		sw.switchBracketCount++;
		if (lookingForCaseBracket)
		{
			sw.unindentCase = true;
			sw.unindentDepth++;
			lookingForCaseBracket = false;
		}
		return i;
	}
	lookingForCaseBracket = false;

	if (line[i] == '}')
	{
		sw.switchBracketCount--;
		assert(sw.switchBracketCount <= bracketCount);
		if (sw.switchBracketCount == 0)
		{
			int lineUnindent = sw.unindentDepth;
			if (line.find_first_not_of(" \t") == i
			        && !switchStack.empty())
				lineUnindent = switchStack[switchStack.size() - 1].unindentDepth;
			if (shouldUnindentLine)
			{
				if (lineUnindent > 0)
					i -= unindentLine(line, lineUnindent);
				shouldUnindentLine = false;
			}
			switchDepth--;
			sw = switchStack.back();
			switchStack.pop_back();
		}
		return i;
	}

	if (isPotentialKeyword
	        && (findKeyword(line, i, "case") || findKeyword(line, i, "default")))
	{
		if (sw.unindentCase)
		{
			sw.unindentCase = false;
			sw.unindentDepth--;
		}

		i = findCaseColon(line, i);

		i++;
		for (; i < line.length(); i++)
		{
			if (!isWhiteSpace(line[i]))
				break;
		}
		if (i < line.length())
		{
			if (line[i] == '{')
			{
				bracketCount++;
				sw.switchBracketCount++;
				if (!isOneLineBlockReached(line, i))
					unindentNextLine = true;
				return i;
			}
		}
		lookingForCaseBracket = true;
		i--;
		return i;
	}
	if (isPotentialKeyword)
	{
		string name = getCurrentWord(line, i);
		i += name.length() - 1;
	}
	return i;
}
