getVectorizedFunction(StringRef F,
                                                       unsigned VF) const {
  F = sanitizeFunctionName(F);
  if (F.empty())
    return F;
  std::vector<VecDesc>::const_iterator I = std::lower_bound(
      VectorDescs.begin(), VectorDescs.end(), F, compareWithScalarFnName);
  while (I != VectorDescs.end() && StringRef(I->ScalarFnName) == F) {
    if (I->VectorizationFactor == VF)
      return I->VectorFnName;
    ++I;
  }
  return StringRef();
}
