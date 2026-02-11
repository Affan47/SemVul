recheckIgnoredWords(void)
{

	UT_GrowBuf pgb(1024);
	bool bRes = getBlockBuf(&pgb);
	UT_UNUSED(bRes);
	UT_ASSERT(bRes);
	const UT_UCSChar* pBlockText = reinterpret_cast<UT_UCSChar*>(pgb.getPointer(0));

	bool bUpdate = m_pSpellSquiggles->recheckIgnoredWords(pBlockText);


	FV_View* pView = getView();
	if (bUpdate && pView)
	{
		pView->updateScreen();
	}
}
