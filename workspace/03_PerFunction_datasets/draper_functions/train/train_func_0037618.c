removeRun(fp_Run* pRun, bool bTellTheRunAboutIt)
{


        if(pRun->getType() == FPRUN_FORCEDPAGEBREAK)
	{
	    getBlock()->forceSectionBreak();
	}
	if (bTellTheRunAboutIt)
	{
	        if(pRun == getLastRun())
	        {
		     clearScreenFromRunToEnd(pRun);
		}
		pRun->setLine(NULL);
	}

	UT_sint32 ndx = m_vecRuns.findItem(pRun);
	UT_return_val_if_fail(ndx>=0,false);
	m_vecRuns.deleteNthItem(ndx);

	removeDirectionUsed(pRun->getDirection());

	return true;
}
