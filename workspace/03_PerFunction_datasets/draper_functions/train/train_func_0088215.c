EmitWinCFIAllocStack(unsigned Size) {
  EnsureValidWinFrameInfo();
  if (Size == 0)
    report_fatal_error("Allocation size must be non-zero!");
  if (Size & 7)
    report_fatal_error("Misaligned stack allocation!");

  MCSymbol *Label = getContext().createTempSymbol();
  EmitLabel(Label);

  WinEH::Instruction Inst = Win64EH::Instruction::Alloc(Label, Size);
  CurrentWinFrameInfo->Instructions.push_back(Inst);
}
