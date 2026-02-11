isSrcOp(X86Operand &Op) {
  unsigned basereg = is64BitMode() ? X86::RSI : X86::ESI;

  return (Op.isMem() &&
    (Op.Mem.SegReg == 0 || Op.Mem.SegReg == X86::DS) &&
    isa<MCConstantExpr>(Op.Mem.Disp) &&
    cast<MCConstantExpr>(Op.Mem.Disp)->getValue() == 0 &&
    Op.Mem.BaseReg == basereg && Op.Mem.IndexReg == 0);
}
