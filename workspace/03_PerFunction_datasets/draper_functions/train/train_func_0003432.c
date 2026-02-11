SelectIntCast(const Instruction *I) {


  Type *DestTy = I->getType();
  Value *Op = I->getOperand(0);
  Type *SrcTy = Op->getType();

  EVT SrcVT, DestVT;
  SrcVT = TLI.getValueType(SrcTy, true);
  DestVT = TLI.getValueType(DestTy, true);

  if (isa<TruncInst>(I)) {
    if (SrcVT != MVT::i32 && SrcVT != MVT::i16 && SrcVT != MVT::i8)
      return false;
    if (DestVT != MVT::i16 && DestVT != MVT::i8 && DestVT != MVT::i1)
      return false;

    unsigned SrcReg = getRegForValue(Op);
    if (!SrcReg) return false;


    UpdateValueMap(I, SrcReg);
    return true;
  }
  if (DestVT != MVT::i32 && DestVT != MVT::i16 && DestVT != MVT::i8)
    return false;

  unsigned Opc;
  bool isZext = isa<ZExtInst>(I);
  bool isBoolZext = false;
  if (!SrcVT.isSimple())
    return false;
  switch (SrcVT.getSimpleVT().SimpleTy) {
  default: return false;
  case MVT::i16:
    if (!Subtarget->hasV6Ops()) return false;
    if (isZext)
      Opc = isThumb ? ARM::t2UXTH : ARM::UXTH;
    else
      Opc = isThumb ? ARM::t2SXTH : ARM::SXTH;
    break;
  case MVT::i8:
    if (!Subtarget->hasV6Ops()) return false;
    if (isZext)
      Opc = isThumb ? ARM::t2UXTB : ARM::UXTB;
    else
      Opc = isThumb ? ARM::t2SXTB : ARM::SXTB;
    break;
  case MVT::i1:
    if (isZext) {
      Opc = isThumb ? ARM::t2ANDri : ARM::ANDri;
      isBoolZext = true;
      break;
    }
    return false;
  }


  unsigned SrcReg = getRegForValue(Op);
  if (!SrcReg) return false;

  unsigned DestReg = createResultReg(TLI.getRegClassFor(MVT::i32));
  MachineInstrBuilder MIB;
  MIB = BuildMI(*FuncInfo.MBB, FuncInfo.InsertPt, DL, TII.get(Opc), DestReg)
        .addReg(SrcReg);
  if (isBoolZext)
    MIB.addImm(1);
  else
    MIB.addImm(0);
  AddOptionalDefs(MIB);
  UpdateValueMap(I, DestReg);
  return true;
}
