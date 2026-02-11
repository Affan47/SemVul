infoassembly_calculateGc(const char* bases,
                                    int startIndex,
                                    int endIndex,
                                    CalculateGcState state)
{
    int i=0;

    if (state.init)
    {
	state.init = ajFalse ;
	state.gcCount = 0;
	state.nCount  = 0;

	for (i=startIndex; i<endIndex; ++i)
	{
	    char base = bases[i];

	    if (base == 'G' || base == 'C')
		++state.gcCount;
	    else if (base == 'N')
		++state.nCount;
	}
    }
    else
    {
	char newBase = bases[endIndex-1];

	if (newBase == 'G' || newBase == 'C')
	    ++state.gcCount;
	else if (newBase == 'N')
	    ++state.nCount;

	if (state.priorBase == 'G' || state.priorBase == 'C')
	    --state.gcCount;
	else if (state.priorBase == 'N')
	    --state.nCount;
    }

    state.priorBase = bases[startIndex];

    if (state.nCount > 4)
	return -1;
    else
	return (state.gcCount * 100) / (endIndex - startIndex);
}
