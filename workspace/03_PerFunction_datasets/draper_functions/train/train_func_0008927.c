PatternLoop(MODCHANNEL *pChn, UINT param)

{
	if (param)
	{
		if (pChn->nPatternLoopCount)
		{
			pChn->nPatternLoopCount--;
			if (!pChn->nPatternLoopCount) return -1;
		} else
		{
			MODCHANNEL *p = Chn;
			for (UINT i=0; i<m_nChannels; i++, p++) if (p != pChn)
			{

				if (p->nPatternLoopCount) return -1;
			}
			pChn->nPatternLoopCount = param;
		}
		return pChn->nPatternLoop;
	} else
	{
		pChn->nPatternLoop = m_nRow;
	}
	return -1;
}
