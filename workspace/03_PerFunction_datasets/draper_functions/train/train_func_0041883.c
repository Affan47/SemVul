fastMaterializeConstant(const Constant *C) {
  EVT CEVT = TLI.getValueType(DL, C->getType(), true);


  if (!CEVT.isSimple()) return 0;
  MVT VT = CEVT.getSimpleVT();

  if (const ConstantFP *CFP = dyn_cast<ConstantFP>(C))
    return ARMMaterializeFP(CFP, VT);
  else if (const GlobalValue *GV = dyn_cast<GlobalValue>(C))
    return ARMMaterializeGV(GV, VT);
  else if (isa<ConstantInt>(C))
    return ARMMaterializeInt(C, VT);

  return 0;
}
