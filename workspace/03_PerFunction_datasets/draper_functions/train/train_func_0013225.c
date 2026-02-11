StartStream()
	{
		m_startedStream = true;
		m_simpleKeyAllowed = true;
		std::auto_ptr<IndentMarker> pIndent(new IndentMarker(-1, IndentMarker::NONE));
		m_indentRefs.push_back(pIndent);
		m_indents.push(&m_indentRefs.back());
	}
