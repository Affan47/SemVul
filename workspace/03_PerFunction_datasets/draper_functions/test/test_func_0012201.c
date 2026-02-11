getBlockFromSDH(pf_Frag_Strux* sdh)
{
	fl_ContainerLayout* sfh = NULL;
	fl_BlockLayout * pBlock = NULL;


	sfh = m_pDoc->getNthFmtHandle(sdh, m_pLayout->getLID());
	if(sfh != NULL)
	{
		pBlock = static_cast<fl_BlockLayout *>(sfh);
		if(pBlock->getDocLayout() != m_pLayout)
		{
			UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
			pBlock = NULL;
		}
	}
	return pBlock;
}
