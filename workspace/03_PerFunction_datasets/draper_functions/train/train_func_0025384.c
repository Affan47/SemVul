IsInCycle (Cycle* pCycle)
{
	std::list<Cycle*>::iterator i, end = m_Cycles.end ();
	for (i = m_Cycles.begin (); i != end; i++)
		if ((*i) == pCycle)
			return true;
	return false;
}
