InitStartEndWord()
{
  FactorCollection &factorCollection = FactorCollection::Instance();

  Word startWord(Input);
  const Factor *factor = factorCollection.AddFactor(Input, 0, BOS_);
  startWord.SetFactor(0, factor);
  PrependWord(startWord);

  Word endWord(Input);
  factor = factorCollection.AddFactor(Input, 0, EOS_);
  endWord.SetFactor(0, factor);
  AddWord(endWord);
}
