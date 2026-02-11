MergeFactors(const Phrase &copy, FactorType factorType)
{
  CHECK(GetSize() == copy.GetSize());
  for (size_t currPos = 0 ; currPos < GetSize() ; currPos++)
    SetFactor(currPos, factorType, copy.GetFactor(currPos, factorType));
}
