SetTypeToScalar(uint64_t iBitWith, uint64_t iMantissa, bool bSigned, ElementSemanticTable semantic) {
  vector<ElementSemanticTable> vSemantic;
  vSemantic.push_back(semantic);
  SetTypeToVector(iBitWith, iMantissa, bSigned, vSemantic);
}
