HandleOptionalItems(std::vector<GdlRule*> & vpruleNewList)
{
	Assert(m_viritOptRangeStart.size() == m_viritOptRangeEnd.size());

	if (m_viritOptRangeStart.size() == 0)
	{
		vpruleNewList.push_back(this);
		return false;
	}

	if (!AdjustOptRanges())
	{
		return false;
	}

	std::vector<bool> vfOmit;
	for (size_t irange = 0; irange < m_viritOptRangeStart.size(); ++irange)
		vfOmit.push_back(false);
	Assert(vfOmit.size() == m_viritOptRangeStart.size());

	GenerateOptRanges(vpruleNewList, vfOmit, 0);

	return true;
}
