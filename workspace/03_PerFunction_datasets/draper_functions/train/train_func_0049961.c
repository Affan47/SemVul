MakePrefixNgrams(std::vector<const Word*> &contextFactor, ScoreComponentCollection* accumulator, size_t numberOfStartPos, size_t offset) const {
	stringstream ngram;
	size_t size = contextFactor.size();
  for (size_t k = 0; k < numberOfStartPos; ++k) {
    size_t max_end = (size < m_n+k+offset)? size: m_n+k+offset;
    for (size_t end_pos = 1+k+offset; end_pos < max_end; ++end_pos) {
      ngram << m_baseName;
    	for (size_t i=k+offset; i <= end_pos; ++i) {
      	if (i > k+offset)
      		ngram << ":";
        string factorZero = (*contextFactor[i]).GetString(0);
        if (m_factorType == 0 || factorZero.compare("<s>") == 0 || factorZero.compare("</s>") == 0)
      		ngram << factorZero;
      	else
      		ngram << (*contextFactor[i]).GetString(m_factorType);
      	const Word w = *contextFactor[i];
      }

      accumulator->SparsePlusEquals(ngram.str(), 1);
      ngram.str("");
    }
  }
}
