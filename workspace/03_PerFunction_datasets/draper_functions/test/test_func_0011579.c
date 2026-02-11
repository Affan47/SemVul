EncodeAddrModeOpValues(const MCInst &MI, unsigned OpIdx, unsigned &Reg,
                       unsigned &Imm, SmallVectorImpl<MCFixup> &Fixups,
 const MCSubtargetInfo &STI) const {
  const MCOperand &MO  = MI.getOperand(OpIdx);
  const MCOperand &MO1 = MI.getOperand(OpIdx + 1);

  Reg = CTX.getRegisterInfo()->getEncodingValue(MO.getReg());

  int32_t SImm = MO1.getImm();
  bool isAdd = true;


  if (SImm == INT32_MIN) {
    SImm = 0;
    isAdd = false;
  }


  if (SImm < 0) {
    SImm = -SImm;
    isAdd = false;
  }

  Imm = SImm;
  return isAdd;
}
