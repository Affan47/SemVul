appendSequence(const string &sequence, bool canBreakLine)
{
	if (canBreakLine && isInLineBreak)
		breakLine();
	formattedLine.append(sequence);
	if (maxCodeLength != string::npos)
	{
		updateFormattedLineSplitPointSequence(sequence);
		testForTimeToSplitFormattedLine(sequence.length());
	}
}
