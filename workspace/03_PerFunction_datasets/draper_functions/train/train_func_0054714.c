SelectFPToSI(const Instruction *I) {

  if (!Subtarget->hasVFP2()) return false;

  MVT DstVT;
  Type *RetTy = I->getType();
  if (!isTypeLegal(RetTy, DstVT))
    return false;

  unsigned Op = getRegForValue(I->getOperand(0));
  if (Op == 0) return false;

  unsigned Opc;
  Type *OpTy = I->getOperand(0)->getType();
  if (OpTy->isFloatTy()) Opc = ARM::VTOSIZS;
  else if (OpTy->isDoubleTy()) Opc = ARM::VTOSIZD;
  else return false;


  unsigned ResultReg = createResultReg(TLI.getRegClassFor(MVT::f32));
  AddOptionalDefs(BuildMI(*FuncInfo.MBB, FuncInfo.InsertPt, DL, TII.get(Opc),
                          ResultReg)
                  .addReg(Op));


  unsigned IntReg = ARMMoveToIntReg(DstVT, ResultReg);
  if (IntReg == 0) return false;

  UpdateValueMap(I, IntReg);
  return true;
}
