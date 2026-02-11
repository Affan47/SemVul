getLineFromPos(s32 pos)
{
	if (!WordWrap && !MultiLine)
		return 0;

	s32 i=0;
	while (i < (s32)BrokenTextPositions.size())
	{
		if (BrokenTextPositions[i] > pos)
			return i-1;
		++i;
	}
	return (s32)BrokenTextPositions.size() - 1;
}
