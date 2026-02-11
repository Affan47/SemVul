materialize32BitInt(int64_t Imm,
                                           const TargetRegisterClass *RC) {
  unsigned ResultReg = createResultReg(RC);

  if (isInt<16>(Imm)) {
    unsigned Opc = Mips::ADDiu;
    emitInst(Opc, ResultReg).addReg(Mips::ZERO).addImm(Imm);
    return ResultReg;
  } else if (isUInt<16>(Imm)) {
    emitInst(Mips::ORi, ResultReg).addReg(Mips::ZERO).addImm(Imm);
    return ResultReg;
  }
  unsigned Lo = Imm & 0xFFFF;
  unsigned Hi = (Imm >> 16) & 0xFFFF;
  if (Lo) {

    unsigned TmpReg = createResultReg(RC);
    emitInst(Mips::LUi, TmpReg).addImm(Hi);
    emitInst(Mips::ORi, ResultReg).addReg(TmpReg).addImm(Lo);
  } else {
    emitInst(Mips::LUi, ResultReg).addImm(Hi);
  }
  return ResultReg;
}
