X86SelectFPTrunc(const Instruction *I) {
  if (Subtarget->hasSSE2()) {
    if (I->getType()->isFloatTy()) {
      const Value *V = I->getOperand(0);
      if (V->getType()->isDoubleTy()) {
        unsigned OpReg = getRegForValue(V);
        if (OpReg == 0) return false;
        unsigned ResultReg = createResultReg(X86::FR32RegisterClass);
        BuildMI(*FuncInfo.MBB, FuncInfo.InsertPt, DL,
                TII.get(X86::CVTSD2SSrr), ResultReg)
          .addReg(OpReg);
        UpdateValueMap(I, ResultReg);
        return true;
      }
    }
  }

  return false;
}
