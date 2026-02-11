calculateWidthOfLine(void)
{
	const UT_sint32 iCountRuns = m_vecRuns.getItemCount();
	UT_sint32 iX = 0;


	for (UT_sint32 i = 0; i < iCountRuns; ++i)
	{
		const fp_Run* pRun = m_vecRuns.getNthItem(i);

		if(pRun->isHidden())
			continue;

		iX += pRun->getWidth();
	}


	m_iWidth = iX;

	return iX;
}
