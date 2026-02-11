GetStringRep(const vector<FactorType> factorsToPrint) const
{
  stringstream strme;
  for (size_t pos = 0 ; pos < GetSize() ; pos++) {
    strme << GetWord(pos).GetString(factorsToPrint, (pos != GetSize()-1));
  }

  return strme.str();
}
