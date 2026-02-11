freeStackSlotBefore(MachineBasicBlock::iterator I, unsigned FPRegNo) {
  unsigned STReg    = getSTReg(FPRegNo);
  unsigned OldSlot  = getSlot(FPRegNo);
  unsigned TopReg   = Stack[StackTop-1];
  Stack[OldSlot]    = TopReg;
  RegMap[TopReg]    = OldSlot;
  RegMap[FPRegNo]   = ~0;
  Stack[--StackTop] = ~0;
  return BuildMI(*MBB, I, DebugLoc(), TII->get(X86::ST_FPrr))
      .addReg(STReg)
      .getInstr();
}
