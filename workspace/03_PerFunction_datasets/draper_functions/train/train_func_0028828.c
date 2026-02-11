CacheLexReordering()
{
  const vector<LexicalReordering*> &lexReorderingModels = m_system->GetReorderModels();
  std::vector<LexicalReordering*>::const_iterator iterLexreordering;

  size_t size = m_source.GetSize();
  for (iterLexreordering = lexReorderingModels.begin() ; iterLexreordering != lexReorderingModels.end() ; ++iterLexreordering) {
    LexicalReordering &lexreordering = **iterLexreordering;

    for (size_t startPos = 0 ; startPos < size ; startPos++) {
      size_t maxSize =  size - startPos;
      size_t maxSizePhrase = StaticData::Instance().GetMaxPhraseLength();
      maxSize = std::min(maxSize, maxSizePhrase);

      for (size_t endPos = startPos ; endPos < startPos + maxSize; endPos++) {
        TranslationOptionList &transOptList = GetTranslationOptionList( startPos, endPos);
        TranslationOptionList::iterator iterTransOpt;
        for(iterTransOpt = transOptList.begin() ; iterTransOpt != transOptList.end() ; ++iterTransOpt) {
          TranslationOption &transOpt = **iterTransOpt;

          const Phrase *sourcePhrase = transOpt.GetSourcePhrase();
          if (sourcePhrase) {
            Scores score = lexreordering.GetProb(*sourcePhrase
                                                 , transOpt.GetTargetPhrase());
            if (!score.empty())
              transOpt.CacheScores(lexreordering, score);
          }
        }
      }
    }
  }
}
