ProcessResult(const CUInt128& target, const CUInt128& answer, TagPtrList *info)
{

	CSearch *s = NULL;
	SearchMap::const_iterator it = m_searches.find(target);
	if (it != m_searches.end()) {
		s = it->second;
	}


	if (s == NULL) {
		AddDebugLogLineN(logKadSearch,
			wxT("Search either never existed or receiving late results (CSearchManager::ProcessResult)"));
	} else {
		s->ProcessResult(answer, info);
	}
}
