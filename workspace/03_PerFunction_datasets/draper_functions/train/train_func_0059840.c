PrevRangeSubsumes(int irangeCurr)
{

	for (int irange = irangeCurr; --irange >= 0; )
	{
		if (m_viritOptRangeStart[irange] <= m_viritOptRangeStart[irangeCurr] &&
				m_viritOptRangeEnd[irangeCurr] <= m_viritOptRangeEnd[irange])
			return irange;
	}
	return -1;
}
