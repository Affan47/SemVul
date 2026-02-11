HasOverlapWith(GdlGlyphClassMember * pglfdLeft, GrcFont * pfont)
{
	for (size_t iglfd = 0; iglfd < m_vpglfdMembers.size(); iglfd++)
	{
		if (m_vpglfdMembers[iglfd]->HasOverlapWith(pglfdLeft, pfont))
			return true;
	}
	return false;
}
