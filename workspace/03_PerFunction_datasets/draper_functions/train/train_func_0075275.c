markDirtyOverlappingRuns(fp_FrameContainer * pFrameC)
{
	UT_Rect * pMyFrameRect = pFrameC->getScreenRect();
	if(pMyFrameRect == NULL)
	{
		UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
		return;
	}


	UT_sint32 count = m_vecColumnLeaders.getItemCount();
	UT_sint32 i = 0;
	for (i=0; i<count; i++)
	{
		fp_Column* pCol = m_vecColumnLeaders.getNthItem(i);
		while (pCol)
		{
			pCol->markDirtyOverlappingRuns(*pMyFrameRect);
			pCol = pCol->getFollower();
		}
	}


	if (m_pHeader)
	{
		m_pHeader->markDirtyOverlappingRuns(*pMyFrameRect);
	}

	if (m_pFooter)
	{
		m_pFooter->markDirtyOverlappingRuns(*pMyFrameRect);
	}


	count = m_vecFootnotes.getItemCount();
	for (i=0; i<count; i++)
	{
		fp_FootnoteContainer* pFC = m_vecFootnotes.getNthItem(i);
		pFC->markDirtyOverlappingRuns(*pMyFrameRect);
	}


	if(getDocLayout()->displayAnnotations())
	{
			count = m_vecAnnotations.getItemCount();
			for (i=0; i<count; i++)
			{
					fp_AnnotationContainer* pAC = m_vecAnnotations.getNthItem(i);
					pAC->markDirtyOverlappingRuns(*pMyFrameRect);
			}
	}


	count = m_vecAboveFrames.getItemCount();
	for (i=0; i<count; i++)
	{
		fp_FrameContainer* pFC = m_vecAboveFrames.getNthItem(i);
		if(pFC != pFrameC)
		{
			pFC->markDirtyOverlappingRuns(*pMyFrameRect);
		}
	}


	count = m_vecBelowFrames.getItemCount();
	for (i=0; i<count; i++)
	{
		fp_FrameContainer* pFC = m_vecBelowFrames.getNthItem(i);
		if(pFC != pFrameC)
		{
			pFC->markDirtyOverlappingRuns(*pMyFrameRect);
		}
	}
	DELETEP(pMyFrameRect);
}
