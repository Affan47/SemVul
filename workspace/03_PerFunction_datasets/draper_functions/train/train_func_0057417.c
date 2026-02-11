DecodeCtrRegs64RegisterClass(MCInst &Inst, unsigned RegNo,
                                                 uint64_t ,
                                                 void const *Decoder) {
  static const uint16_t CtrlReg64DecoderTable[] = {
      Hexagon::C1_0,       Hexagon::NoRegister, Hexagon::C3_2,
      Hexagon::NoRegister, Hexagon::NoRegister, Hexagon::NoRegister,
      Hexagon::C7_6,       Hexagon::NoRegister, Hexagon::C9_8,
      Hexagon::NoRegister, Hexagon::C11_10,     Hexagon::NoRegister,
      Hexagon::CS,         Hexagon::NoRegister, Hexagon::UPC,
      Hexagon::NoRegister};

  if (RegNo >= sizeof(CtrlReg64DecoderTable) / sizeof(CtrlReg64DecoderTable[0]))
    return MCDisassembler::Fail;

  if (CtrlReg64DecoderTable[RegNo] == Hexagon::NoRegister)
    return MCDisassembler::Fail;

  unsigned Register = CtrlReg64DecoderTable[RegNo];
  Inst.addOperand(MCOperand::createReg(Register));
  return MCDisassembler::Success;
}
