join(UT_sint32 iOffset, fl_BlockLayout* pPrevBL)
{

	if (m_pOwner->isHdrFtr())
		return;


	if (!m_pOwner->getDocLayout()->getAutoSpellCheck() && (getSquiggleType() ==  FL_SQUIGGLE_SPELL) )
		return;

	xxx_UT_DEBUGMSG(("fl_Squiggles::join(%d, %p)\n", iOffset, pPrevBL));

	bool bFullCheck = m_pOwner->getDocLayout()->dequeueBlockForBackgroundCheck(m_pOwner);
	bFullCheck |= m_pOwner->getDocLayout()->dequeueBlockForBackgroundCheck(pPrevBL);

	if (bFullCheck)
	{


		deleteAll();
		pPrevBL->getSpellSquiggles()->deleteAll();
		pPrevBL->checkSpelling();
	}
	else
	{


		_deleteAtOffset(0);

		_move(0, iOffset, pPrevBL);
	}
	m_pOwner->getDocLayout()->setPendingBlockForGrammar(m_pOwner);


	if(getSquiggleType() ==  FL_SQUIGGLE_SPELL)
	{
	  fl_Squiggles * pSq = pPrevBL->getSpellSquiggles();
	  UT_return_if_fail( pSq );

	  pSq->_deleteAtOffset(iOffset);


	  pPrevBL->_recalcPendingWord(iOffset, 0);
	}
}
