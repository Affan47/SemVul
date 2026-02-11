related(const Value *A, const Value *B) {


  if (A > B) std::swap(A, B);
  std::pair<CachedResultsTy::iterator, bool> Pair =
    CachedResults.insert(std::make_pair(ValuePairTy(A, B), true));
  if (!Pair.second)
    return Pair.first->second;

  bool Result = relatedCheck(A, B);
  CachedResults[ValuePairTy(A, B)] = Result;
  return Result;
}
