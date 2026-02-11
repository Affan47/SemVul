emitCFIInstruction(const MCCFIInstruction &Inst) const {
  switch (Inst.getOperation()) {
  default:
    llvm_unreachable("Unexpected instruction");
  case MCCFIInstruction::OpDefCfaOffset:
    OutStreamer->EmitCFIDefCfaOffset(Inst.getOffset());
    break;
  case MCCFIInstruction::OpAdjustCfaOffset:
    OutStreamer->EmitCFIAdjustCfaOffset(Inst.getOffset());
    break;
  case MCCFIInstruction::OpDefCfa:
    OutStreamer->EmitCFIDefCfa(Inst.getRegister(), Inst.getOffset());
    break;
  case MCCFIInstruction::OpDefCfaRegister:
    OutStreamer->EmitCFIDefCfaRegister(Inst.getRegister());
    break;
  case MCCFIInstruction::OpOffset:
    OutStreamer->EmitCFIOffset(Inst.getRegister(), Inst.getOffset());
    break;
  case MCCFIInstruction::OpRegister:
    OutStreamer->EmitCFIRegister(Inst.getRegister(), Inst.getRegister2());
    break;
  case MCCFIInstruction::OpWindowSave:
    OutStreamer->EmitCFIWindowSave();
    break;
  case MCCFIInstruction::OpSameValue:
    OutStreamer->EmitCFISameValue(Inst.getRegister());
    break;
  case MCCFIInstruction::OpGnuArgsSize:
    OutStreamer->EmitCFIGnuArgsSize(Inst.getOffset());
    break;
  case MCCFIInstruction::OpEscape:
    OutStreamer->EmitCFIEscape(Inst.getValues());
    break;
  }
}
