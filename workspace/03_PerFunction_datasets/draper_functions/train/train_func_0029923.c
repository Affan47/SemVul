LoadCorpus(InputFileStream& corpus, const FactorList& factors,
	std::vector<wordID_t>& cArray, std::vector<wordID_t>& sntArray,
  Vocab* vocab)
{
	std::string line, word;
	int sntIdx(0);

	const std::string& factorDelimiter = StaticData::Instance().GetFactorDelimiter();
	while(getline(corpus, line)) {
		sntArray.push_back(sntIdx);
		Phrase phrase(ARRAY_SIZE_INCR);

		phrase.CreateFromString( factors, line, factorDelimiter);

		for( size_t i = 0; i < phrase.GetSize(); ++i) {
			cArray.push_back( vocab->GetWordID(phrase.GetWord(i)) );
		}
		sntIdx += phrase.GetSize();
	}

  vocab->MakeClosed();
	return cArray.size();
}
