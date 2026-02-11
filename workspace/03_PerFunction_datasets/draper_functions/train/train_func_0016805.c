selectDivRem(const Instruction *I, unsigned ISDOpcode) {
  EVT DestEVT = TLI.getValueType(DL, I->getType(), true);
  if (!DestEVT.isSimple())
    return false;

  MVT DestVT = DestEVT.getSimpleVT();
  if (DestVT != MVT::i32)
    return false;

  unsigned DivOpc;
  switch (ISDOpcode) {
  default:
    return false;
  case ISD::SDIV:
  case ISD::SREM:
    DivOpc = Mips::SDIV;
    break;
  case ISD::UDIV:
  case ISD::UREM:
    DivOpc = Mips::UDIV;
    break;
  }

  unsigned Src0Reg = getRegForValue(I->getOperand(0));
  unsigned Src1Reg = getRegForValue(I->getOperand(1));
  if (!Src0Reg || !Src1Reg)
    return false;

  emitInst(DivOpc).addReg(Src0Reg).addReg(Src1Reg);
  emitInst(Mips::TEQ).addReg(Src1Reg).addReg(Mips::ZERO).addImm(7);

  unsigned ResultReg = createResultReg(&Mips::GPR32RegClass);
  if (!ResultReg)
    return false;

  unsigned MFOpc = (ISDOpcode == ISD::SREM || ISDOpcode == ISD::UREM)
                       ? Mips::MFHI
                       : Mips::MFLO;
  emitInst(MFOpc, ResultReg);

  updateValueMap(I, ResultReg);
  return true;
}
