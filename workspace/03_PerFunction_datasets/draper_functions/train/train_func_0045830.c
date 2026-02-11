DebugFsmState(std::ostream & strmOut, int )
{
	strmOut << "\n   Matched=";
	std::set<int>::iterator it;
	for (it = m_setiruleMatched.begin();
		it != m_setiruleMatched.end();
		++it)
	{
		strmOut << *it << ",";
	}
	if (m_setiruleMatched.size() == 0)
		strmOut << "none";

	strmOut << "\n   Success=";
	for (it = m_setiruleSuccess.begin();
		it != m_setiruleSuccess.end();
		++it)
	{
		strmOut << *it << ",";
	}
	if (m_setiruleSuccess.size() == 0)
		strmOut << "none";
	strmOut << "\n";
}
