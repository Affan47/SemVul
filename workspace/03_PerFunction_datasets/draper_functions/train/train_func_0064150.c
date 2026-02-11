removeEndnote(fl_EndnoteLayout * pFL)
{
	UT_sint32 i = m_vecEndnotes.findItem(pFL);
	if(i< 0)
	{
		return;
	}
	m_vecEndnotes.deleteNthItem(i);
}
