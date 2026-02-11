viewTop(void ** ppVoid) const
{
	UT_ASSERT(ppVoid);
	UT_uint32 indexEnd = m_vecStack.getItemCount();
	if (!indexEnd) {
		*ppVoid = 0;
		return false;
	}
	*ppVoid = const_cast<void*>(m_vecStack.getLastItem());
	return true;
}
