getRegForValue(const Value *V) {
  EVT RealVT = TLI.getValueType(V->getType(), true);

  if (!RealVT.isSimple())
    return 0;


  MVT VT = RealVT.getSimpleVT();
  if (!TLI.isTypeLegal(VT)) {

    if (VT == MVT::i1 || VT == MVT::i8 || VT == MVT::i16)
      VT = TLI.getTypeToTransformTo(V->getContext(), VT).getSimpleVT();
    else
      return 0;
  }


  DenseMap<const Value *, unsigned>::iterator I = FuncInfo.ValueMap.find(V);
  if (I != FuncInfo.ValueMap.end())
    return I->second;

  unsigned Reg = LocalValueMap[V];
  if (Reg != 0)
    return Reg;


  if (isa<Instruction>(V) &&
      (!isa<AllocaInst>(V) ||
       !FuncInfo.StaticAllocaMap.count(cast<AllocaInst>(V))))
    return FuncInfo.InitializeRegForValue(V);

  SavePoint SaveInsertPt = enterLocalValueArea();


  Reg = materializeRegForValue(V, VT);

  leaveLocalValueArea(SaveInsertPt);

  return Reg;
}
