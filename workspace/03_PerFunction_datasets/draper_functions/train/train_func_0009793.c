printOperand(const MCInst *MI, unsigned OpNo,
                                     raw_ostream &O) {

  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg()) {
    switch (Op.getReg()) {

    case AMDGPU::PRED_SEL_OFF:
      break;

    default:
      printRegOperand(Op.getReg(), O, MRI);
      break;
    }
  } else if (Op.isImm()) {
    const MCInstrDesc &Desc = MII.get(MI->getOpcode());
    int RCID = Desc.OpInfo[OpNo].RegClass;
    if (RCID != -1) {
      const MCRegisterClass &ImmRC = MRI.getRegClass(RCID);
      if (ImmRC.getSize() == 4)
        printImmediate32(Op.getImm(), O);
      else if (ImmRC.getSize() == 8)
        printImmediate64(Op.getImm(), O);
      else
        llvm_unreachable("Invalid register class size");
    } else if (Desc.OpInfo[OpNo].OperandType == MCOI::OPERAND_IMMEDIATE) {
      printImmediate32(Op.getImm(), O);
    } else {


      O << formatDec(Op.getImm());
    }
  } else if (Op.isFPImm()) {

    if (Op.getFPImm() == 0.0)
      O << "0.0";
    else {
      const MCInstrDesc &Desc = MII.get(MI->getOpcode());
      const MCRegisterClass &ImmRC = MRI.getRegClass(Desc.OpInfo[OpNo].RegClass);

      if (ImmRC.getSize() == 4)
        printImmediate32(FloatToBits(Op.getFPImm()), O);
      else if (ImmRC.getSize() == 8)
        printImmediate64(DoubleToBits(Op.getFPImm()), O);
      else
        llvm_unreachable("Invalid register class size");
    }
  } else if (Op.isExpr()) {
    const MCExpr *Exp = Op.getExpr();
    Exp->print(O, &MAI);
  } else {
    llvm_unreachable("unknown operand type in printOperand");
  }
}
