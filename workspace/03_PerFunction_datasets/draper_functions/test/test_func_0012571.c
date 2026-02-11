findSetStartAt(PT_DocPosition pos)
{
	PT_DocPosition posEnd;
	m_pDoc->getBounds(true, posEnd);
	UT_return_if_fail(pos <= posEnd);

	m_startPosition = pos;
	m_wrappedEnd = false;
	m_doneFind = false;
}
