ExpandINSERT_VECTOR_ELT(SDValue Vec, SDValue Val, SDValue Idx, DebugLoc dl) {
  if (ConstantSDNode *InsertPos = dyn_cast<ConstantSDNode>(Idx)) {


    EVT EltVT = Vec.getValueType().getVectorElementType();
    if (Val.getValueType() == EltVT ||
        (EltVT.isInteger() && Val.getValueType().bitsGE(EltVT))) {
      SDValue ScVec = DAG.getNode(ISD::SCALAR_TO_VECTOR, dl,
                                  Vec.getValueType(), Val);

      unsigned NumElts = Vec.getValueType().getVectorNumElements();


      SmallVector<int, 8> ShufOps;
      for (unsigned i = 0; i != NumElts; ++i)
        ShufOps.push_back(i != InsertPos->getZExtValue() ? i : NumElts);

      return DAG.getVectorShuffle(Vec.getValueType(), dl, Vec, ScVec,
                                  &ShufOps[0]);
    }
  }
  return PerformInsertVectorEltInMemory(Vec, Val, Idx, dl);
}
