formatPointerOrReferenceCast(void)
{
	assert(currentChar == '*' || currentChar == '&' || currentChar == '^');
	assert(!isJavaStyle());

	int pa = pointerAlignment;
	int ra = referenceAlignment;
	int itemAlignment = (currentChar == '*' || currentChar == '^') ? pa : ((ra == REF_SAME_AS_PTR) ? pa : ra);

	string sequenceToInsert(1, currentChar);
	if (isSequenceReached("**"))
	{
		sequenceToInsert = "**";
		goForward(1);
	}
	if (itemAlignment == PTR_ALIGN_NONE)
	{
		appendSequence(sequenceToInsert, false);
		return;
	}

	size_t prevCh = formattedLine.find_last_not_of(" \t");
	if (prevCh == string::npos)
		prevCh = 0;
	if (prevCh + 1 < formattedLine.length()
	        && isWhiteSpace(formattedLine[prevCh+1]))
	{
		spacePadNum -= (formattedLine.length() - 1 - prevCh);
		formattedLine.erase(prevCh+1);
	}
	bool isAfterScopeResolution = previousNonWSChar == ':';
	if ((itemAlignment == PTR_ALIGN_MIDDLE || itemAlignment == PTR_ALIGN_NAME)
	        && !isAfterScopeResolution)
	{
		appendSpacePad();

		if (maxCodeLength != string::npos && formattedLine.length() > 0)
			updateFormattedLineSplitPointsPointerOrReference(formattedLine.length()-1);
		appendSequence(sequenceToInsert, false);
	}
	else
		appendSequence(sequenceToInsert, false);
}
