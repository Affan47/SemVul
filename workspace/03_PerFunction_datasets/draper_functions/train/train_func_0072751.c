queueBlockForBackgroundCheck(UT_uint32 iReason,
										   fl_BlockLayout *pBlock,
										   bool bHead)
{

	if (!m_pBackgroundCheckTimer)
	{
	    int inMode = UT_WorkerFactory::IDLE | UT_WorkerFactory::TIMER;
	    if(getView() && getView()->isGrammarLoaded() && m_bAutoGrammarCheck)
	    {
	         inMode = UT_WorkerFactory::TIMER;
	    }
	    UT_WorkerFactory::ConstructMode outMode = UT_WorkerFactory::NONE;

	    m_pBackgroundCheckTimer = UT_WorkerFactory::static_constructor (_backgroundCheck, this, inMode, outMode);

	    UT_ASSERT(m_pBackgroundCheckTimer);
	    UT_ASSERT(outMode != UT_WorkerFactory::NONE);


	    if ( UT_WorkerFactory::TIMER == outMode )
		{

			static_cast<UT_Timer*>(m_pBackgroundCheckTimer)->set(BACKGROUND_CHECK_MSECS);
		}
#if 1
	    m_bStopSpellChecking = false;
	    m_pBackgroundCheckTimer->start();
#endif

	}
#if 1
	else
	{

		m_bStopSpellChecking = false;
		m_pBackgroundCheckTimer->start();
	}
#endif


	if (hasBackgroundCheckReason(bgcrDebugFlash))
	{
		pBlock->addBackgroundCheckReason(bgcrDebugFlash);
	}
	pBlock->addBackgroundCheckReason(iReason);

	if (!pBlock->isQueued())
	{


		if (bHead)
			pBlock->enqueueToSpellCheckAfter(NULL);
		else
			pBlock->enqueueToSpellCheckAfter(m_toSpellCheckTail);
	}
	else if (bHead)
	{

		pBlock->dequeueFromSpellCheck();
		pBlock->enqueueToSpellCheckAfter(NULL);
	}
}
