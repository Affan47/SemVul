GetShortestRefIndex(size_t ref_id) {

		int shortestRef = -1;
		size_t shortestRefIndex = 0;
		for (size_t i = 0; i < (m_refs[ref_id].first).size(); ++i) {
			if (shortestRef == -1 || (int)(m_refs[ref_id].first)[i] < shortestRef) {
				shortestRef = (m_refs[ref_id].first)[i];
				shortestRefIndex = i;
			}
		}
    return shortestRefIndex;
}
