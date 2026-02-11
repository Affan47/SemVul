TopBotMarginChanged(void)
{


	UT_sint32 iTopM = m_pOwner->getTopMargin();
	UT_sint32 iBotM = m_pOwner->getBottomMargin();
	clearScreenFrames();
	if(m_pHeader)
	{
		m_pHeader->clearScreen();
		m_pHeader->setMaxHeight(iTopM - m_pOwner->getHeaderMargin());
		m_pHeader->layout();
	}
	if(m_pFooter)
	{
		m_pFooter->clearScreen();
		m_pFooter->setMaxHeight(iBotM - m_pOwner->getFooterMargin());
		m_pFooter->setY(getHeight() - iBotM);
		m_pFooter->layout();
	}
	breakPage();
	_reformat();
	return true;
}
