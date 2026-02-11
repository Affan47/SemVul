getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                  SmallVectorImpl<MCFixup> &Fixups) const {
  if (MO.isReg()) {
    unsigned Reg = MO.getReg();
    unsigned RegNo = getARMRegisterNumbering(Reg);


    switch (Reg) {
    default:
      return RegNo;
    case ARM::Q0:  case ARM::Q1:  case ARM::Q2:  case ARM::Q3:
    case ARM::Q4:  case ARM::Q5:  case ARM::Q6:  case ARM::Q7:
    case ARM::Q8:  case ARM::Q9:  case ARM::Q10: case ARM::Q11:
    case ARM::Q12: case ARM::Q13: case ARM::Q14: case ARM::Q15:
      return 2 * RegNo;
    }
  } else if (MO.isImm()) {
    return static_cast<unsigned>(MO.getImm());
  } else if (MO.isFPImm()) {
    return static_cast<unsigned>(APFloat(MO.getFPImm())
                     .bitcastToAPInt().getHiBits(32).getLimitedValue());
  }

  llvm_unreachable("Unable to encode MCOperand!");
  return 0;
}
