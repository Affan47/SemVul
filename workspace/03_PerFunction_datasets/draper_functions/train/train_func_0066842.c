SelectGetElementPtr(const User *I) {
  unsigned N = getRegForValue(I->getOperand(0));
  if (N == 0)

    return false;

  bool NIsKill = hasTrivialKill(I->getOperand(0));

  const Type *Ty = I->getOperand(0)->getType();
  MVT VT = TLI.getPointerTy();
  for (GetElementPtrInst::const_op_iterator OI = I->op_begin()+1,
       E = I->op_end(); OI != E; ++OI) {
    const Value *Idx = *OI;
    if (const StructType *StTy = dyn_cast<StructType>(Ty)) {
      unsigned Field = cast<ConstantInt>(Idx)->getZExtValue();
      if (Field) {

        uint64_t Offs = TD.getStructLayout(StTy)->getElementOffset(Field);


        N = FastEmit_ri_(VT, ISD::ADD, N, NIsKill, Offs, VT);
        if (N == 0)

          return false;
        NIsKill = true;
      }
      Ty = StTy->getElementType(Field);
    } else {
      Ty = cast<SequentialType>(Ty)->getElementType();


      if (const ConstantInt *CI = dyn_cast<ConstantInt>(Idx)) {
        if (CI->isZero()) continue;
        uint64_t Offs =
          TD.getTypeAllocSize(Ty)*cast<ConstantInt>(CI)->getSExtValue();
        N = FastEmit_ri_(VT, ISD::ADD, N, NIsKill, Offs, VT);
        if (N == 0)

          return false;
        NIsKill = true;
        continue;
      }


      uint64_t ElementSize = TD.getTypeAllocSize(Ty);
      std::pair<unsigned, bool> Pair = getRegForGEPIndex(Idx);
      unsigned IdxN = Pair.first;
      bool IdxNIsKill = Pair.second;
      if (IdxN == 0)

        return false;

      if (ElementSize != 1) {
        IdxN = FastEmit_ri_(VT, ISD::MUL, IdxN, IdxNIsKill, ElementSize, VT);
        if (IdxN == 0)

          return false;
        IdxNIsKill = true;
      }
      N = FastEmit_rr(VT, VT, ISD::ADD, N, NIsKill, IdxN, IdxNIsKill);
      if (N == 0)

        return false;
    }
  }


  UpdateValueMap(I, N);
  return true;
}
