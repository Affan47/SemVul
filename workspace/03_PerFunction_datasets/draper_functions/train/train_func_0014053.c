DecodeTestAndBranch(llvm::MCInst &Inst, uint32_t insn,
                                        uint64_t Addr, const void *Decoder) {
  uint64_t Rt = fieldFromInstruction(insn, 0, 5);
  uint64_t bit = fieldFromInstruction(insn, 31, 1) << 5;
  bit |= fieldFromInstruction(insn, 19, 5);
  int64_t dst = fieldFromInstruction(insn, 5, 14);
  const AArch64Disassembler *Dis =
      static_cast<const AArch64Disassembler *>(Decoder);


  if (dst & (1 << (14 - 1)))
    dst |= ~((1LL << 14) - 1);

  if (fieldFromInstruction(insn, 31, 1) == 0)
    DecodeGPR32RegisterClass(Inst, Rt, Addr, Decoder);
  else
    DecodeGPR64RegisterClass(Inst, Rt, Addr, Decoder);
  Inst.addOperand(MCOperand::createImm(bit));
  if (!Dis->tryAddingSymbolicOperand(Inst, dst * 4, Addr, true, 0, 4))
    Inst.addOperand(MCOperand::createImm(dst));

  return Success;
}
