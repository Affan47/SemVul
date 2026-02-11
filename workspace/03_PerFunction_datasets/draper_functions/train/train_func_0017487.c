DecodeSORegRegOperand(MCInst &Inst, unsigned Val,
                               uint64_t Address, const void *Decoder) {
  DecodeStatus S = MCDisassembler::Success;

  unsigned Rm = fieldFromInstruction(Val, 0, 4);
  unsigned type = fieldFromInstruction(Val, 5, 2);
  unsigned Rs = fieldFromInstruction(Val, 8, 4);


  if (!Check(S, DecodeGPRnopcRegisterClass(Inst, Rm, Address, Decoder)))
    return MCDisassembler::Fail;
  if (!Check(S, DecodeGPRnopcRegisterClass(Inst, Rs, Address, Decoder)))
    return MCDisassembler::Fail;

  ARM_AM::ShiftOpc Shift = ARM_AM::lsl;
  switch (type) {
    case 0:
      Shift = ARM_AM::lsl;
      break;
    case 1:
      Shift = ARM_AM::lsr;
      break;
    case 2:
      Shift = ARM_AM::asr;
      break;
    case 3:
      Shift = ARM_AM::ror;
      break;
  }

  Inst.addOperand(MCOperand::createImm(Shift));

  return S;
}
