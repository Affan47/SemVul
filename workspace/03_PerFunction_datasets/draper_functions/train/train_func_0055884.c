containsValue(
    const DataLayout &DL,
    const DenseMap<GlobalObject *, uint64_t> &GlobalLayout, Value *V,
    uint64_t COffset) const {
  if (auto GV = dyn_cast<GlobalObject>(V)) {
    auto I = GlobalLayout.find(GV);
    if (I == GlobalLayout.end())
      return false;
    return containsGlobalOffset(I->second + COffset);
  }

  if (auto GEP = dyn_cast<GEPOperator>(V)) {
    APInt APOffset(DL.getPointerSizeInBits(0), 0);
    bool Result = GEP->accumulateConstantOffset(DL, APOffset);
    if (!Result)
      return false;
    COffset += APOffset.getZExtValue();
    return containsValue(DL, GlobalLayout, GEP->getPointerOperand(),
                         COffset);
  }

  if (auto Op = dyn_cast<Operator>(V)) {
    if (Op->getOpcode() == Instruction::BitCast)
      return containsValue(DL, GlobalLayout, Op->getOperand(0), COffset);

    if (Op->getOpcode() == Instruction::Select)
      return containsValue(DL, GlobalLayout, Op->getOperand(1), COffset) &&
             containsValue(DL, GlobalLayout, Op->getOperand(2), COffset);
  }

  return false;
}
