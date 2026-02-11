ComputeFeatures(const TargetPhrase& targetPhrase,
    											 ScoreComponentCollection* accumulator,
    											 const AlignmentInfo &alignmentInfo) const
{

  size_t targetLength = targetPhrase.GetSize();
  size_t sourceLength = targetPhrase.GetSourcePhrase().GetSize();
  if (targetLength == 1 && sourceLength == 1 && !alignmentInfo.GetSize()) return;


  bool aligned[16];
  CHECK(targetLength < 16);
  for(size_t i=0; i<targetLength; i++) {
    aligned[i] = false;
  }
  for (AlignmentInfo::const_iterator alignmentPoint = alignmentInfo.begin(); alignmentPoint != alignmentInfo.end(); alignmentPoint++) {
    aligned[ alignmentPoint->second ] = true;
  }


  for(size_t i=0; i<targetLength; i++) {
    if (!aligned[i]) {
      Word w = targetPhrase.GetWord(i);
      if (!w.IsNonTerminal()) {
    	const string &word = w.GetFactor(m_factorType)->GetString();
    	if (word != "<s>" && word != "</s>") {
      	  if (!m_unrestricted && m_vocab.find( word ) == m_vocab.end()) {
      		accumulator->PlusEquals(this,"OTHER",1);
      	  }
      	  else {
      		accumulator->PlusEquals(this,word,1);
      	  }
    	}
      }
    }
  }
}
