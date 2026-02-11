DecodeSWAP(MCInst &MI, unsigned insn, uint64_t Address,
                               const void *Decoder) {

  unsigned rd = fieldFromInstruction(insn, 25, 5);
  unsigned rs1 = fieldFromInstruction(insn, 14, 5);
  unsigned isImm = fieldFromInstruction(insn, 13, 1);
  bool hasAsi = fieldFromInstruction(insn, 23, 1);
  unsigned asi = fieldFromInstruction(insn, 5, 8);
  unsigned rs2 = 0;
  unsigned simm13 = 0;
  if (isImm)
    simm13 = SignExtend32<13>(fieldFromInstruction(insn, 0, 13));
  else
    rs2 = fieldFromInstruction(insn, 0, 5);


  DecodeStatus status = DecodeIntRegsRegisterClass(MI, rd, Address, Decoder);
  if (status != MCDisassembler::Success)
    return status;


  status = DecodeIntRegsRegisterClass(MI, rs1, Address, Decoder);
  if (status != MCDisassembler::Success)
    return status;


  if (isImm)
    MI.addOperand(MCOperand::createImm(simm13));
  else {
    status = DecodeIntRegsRegisterClass(MI, rs2, Address, Decoder);
    if (status != MCDisassembler::Success)
      return status;
  }

  if (hasAsi)
    MI.addOperand(MCOperand::createImm(asi));

  return MCDisassembler::Success;
}
