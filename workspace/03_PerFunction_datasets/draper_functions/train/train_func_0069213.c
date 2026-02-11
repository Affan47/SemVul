materializeConstant(const Value *V, MVT VT) {
  unsigned Reg = 0;
  if (const auto *CI = dyn_cast<ConstantInt>(V)) {
    if (CI->getValue().getActiveBits() <= 64)
      Reg = fastEmit_i(VT, VT, ISD::Constant, CI->getZExtValue());
  } else if (isa<AllocaInst>(V))
    Reg = fastMaterializeAlloca(cast<AllocaInst>(V));
  else if (isa<ConstantPointerNull>(V))


    Reg = getRegForValue(
        Constant::getNullValue(DL.getIntPtrType(V->getContext())));
  else if (const auto *CF = dyn_cast<ConstantFP>(V)) {
    if (CF->isNullValue())
      Reg = fastMaterializeFloatZero(CF);
    else

      Reg = fastEmit_f(VT, VT, ISD::ConstantFP, CF);

    if (!Reg) {

      const APFloat &Flt = CF->getValueAPF();
      EVT IntVT = TLI.getPointerTy(DL);

      uint64_t x[2];
      uint32_t IntBitWidth = IntVT.getSizeInBits();
      bool isExact;
      (void)Flt.convertToInteger(x, IntBitWidth, true,
                                 APFloat::rmTowardZero, &isExact);
      if (isExact) {
        APInt IntVal(IntBitWidth, x);

        unsigned IntegerReg =
            getRegForValue(ConstantInt::get(V->getContext(), IntVal));
        if (IntegerReg != 0)
          Reg = fastEmit_r(IntVT.getSimpleVT(), VT, ISD::SINT_TO_FP, IntegerReg,
                           false);
      }
    }
  } else if (const auto *Op = dyn_cast<Operator>(V)) {
    if (!selectOperator(Op, Op->getOpcode()))
      if (!isa<Instruction>(Op) ||
          !fastSelectInstruction(cast<Instruction>(Op)))
        return 0;
    Reg = lookUpRegForValue(Op);
  } else if (isa<UndefValue>(V)) {
    Reg = createResultReg(TLI.getRegClassFor(VT));
    BuildMI(*FuncInfo.MBB, FuncInfo.InsertPt, DbgLoc,
            TII.get(TargetOpcode::IMPLICIT_DEF), Reg);
  }
  return Reg;
}
