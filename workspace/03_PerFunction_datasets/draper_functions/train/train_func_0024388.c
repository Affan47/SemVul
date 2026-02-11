getClosestFootnote(PT_DocPosition pos) const
{
	fl_FootnoteLayout * pFL = NULL;
	fl_FootnoteLayout * pClosest = NULL;
	UT_sint32 i = 0;
	for(i = 0; i< static_cast<UT_sint32>(m_pLayout->countFootnotes());i++)
	{
		pFL = m_pLayout->getNthFootnote(i);
		if(pFL->getDocPosition() <= pos)
		{
			if(pClosest == NULL)
			{
				pClosest = pFL;
			}
			else if( pClosest->getDocPosition() < pFL->getDocPosition())
			{
				pClosest = pFL;
			}
		}
	}
	return pClosest;
}
