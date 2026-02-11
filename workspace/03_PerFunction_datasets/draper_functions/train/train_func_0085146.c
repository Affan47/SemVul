EmitInstruction(const MCInst &Inst,
                                      const MCSubtargetInfo &STI) {
  MCELFStreamer::EmitInstruction(Inst, STI);

  MCContext &Context = getContext();
  const MCRegisterInfo *MCRegInfo = Context.getRegisterInfo();

  for (unsigned OpIndex = 0; OpIndex < Inst.getNumOperands(); ++OpIndex) {
    const MCOperand &Op = Inst.getOperand(OpIndex);

    if (!Op.isReg())
      continue;

    unsigned Reg = Op.getReg();
    RegInfoRecord->SetPhysRegUsed(Reg, MCRegInfo);
  }

  createPendingLabelRelocs();
}
