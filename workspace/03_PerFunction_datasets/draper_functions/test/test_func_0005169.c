getVPermMask(ShuffleVectorSDNode *VSN,
                         SmallVectorImpl<int> &Bytes) {
  EVT VT = VSN->getValueType(0);
  unsigned NumElements = VT.getVectorNumElements();
  unsigned BytesPerElement = VT.getVectorElementType().getStoreSize();
  Bytes.resize(NumElements * BytesPerElement, -1);
  for (unsigned I = 0; I < NumElements; ++I) {
    int Index = VSN->getMaskElt(I);
    if (Index >= 0)
      for (unsigned J = 0; J < BytesPerElement; ++J)
        Bytes[I * BytesPerElement + J] = Index * BytesPerElement + J;
  }
}
