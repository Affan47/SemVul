appendOperator(const string &sequence, bool canBreakLine)
{
	if (canBreakLine && isInLineBreak)
		breakLine();
	formattedLine.append(sequence);
	if (maxCodeLength != string::npos)
	{

		if (isOkToSplitFormattedLine())
			updateFormattedLineSplitPointsOperator(sequence);
		if (formattedLine.length() > maxCodeLength)
			testForTimeToSplitFormattedLine();
	}
}
