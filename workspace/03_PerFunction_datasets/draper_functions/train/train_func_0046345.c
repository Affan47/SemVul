footnoteHeightChanged(void)
{
	clearScreenFootnotes();
	m_pOwner->setNeedsSectionBreak(true,getPrev());
	if(breakPage())
	{
		_reformat();
	}
	else
	{
		UT_DEBUGMSG(("SEVIOR: Mark for rebuild from footnoteheight changed. \n"));
		m_pOwner->markForRebuild();


		UT_ASSERT(0);
	}
}
