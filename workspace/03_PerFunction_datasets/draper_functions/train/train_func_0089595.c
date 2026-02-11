BuildNonTermIndexMap()
{
  if (m_collection.empty()) {
    return;
  }
  const_iterator p = begin();
  size_t maxIndex = p->second;
  for (++p;  p != end(); ++p) {
    if (p->second > maxIndex) {
      maxIndex = p->second;
    }
  }
  m_nonTermIndexMap.resize(maxIndex+1, NOT_FOUND);
  size_t i = 0;
  for (p = begin(); p != end(); ++p) {
  	if (m_nonTermIndexMap[p->second] != NOT_FOUND) {

  		m_nonTermIndexMap.clear();
  		return;
  	}
    m_nonTermIndexMap[p->second] = i++;
  }

}
