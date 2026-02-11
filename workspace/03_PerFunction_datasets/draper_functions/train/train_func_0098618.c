GetCorpusIndex(const vuint_t* phrase, vuint_t* indices)
{
  pair<vuint_t::iterator,vuint_t::iterator> bounds;
  indices->clear();
  size_t phrasesize = phrase->size();

  bounds = std::equal_range(m_F->begin(), m_F->end(), phrase->at(0));

  size_t lwrBnd = size_t(bounds.first - m_F->begin());
  size_t uprBnd = size_t(bounds.second - m_F->begin());


  if(uprBnd - lwrBnd == 0) return false;
  if(phrasesize == 1) {
    for(size_t i=lwrBnd; i < uprBnd; ++i) {
      indices->push_back(m_SA->at(i));
    }
    return (indices->size() > 0);
  }

  for(size_t i = lwrBnd; i < uprBnd; ++i) {
    size_t crpIdx = m_SA->at(i);
    if((crpIdx + phrasesize) > m_corpus->size()) continue;
    for(size_t pos = 1; pos < phrasesize; ++pos) {
      if(m_corpus->at(crpIdx + pos) != phrase->at(pos)) {
        if(indices->size() > 0) i = uprBnd;
        break;
      } else if(pos == phrasesize-1) {
        indices->push_back(crpIdx + pos);
      }
    }
  }

  return (indices->size() > 0);
}
