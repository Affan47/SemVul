findIncDecBefore(MachineBasicBlock::iterator MBBI, unsigned Reg,
                 ARMCC::CondCodes Pred, unsigned PredReg, int &Offset) {
  Offset = 0;
  MachineBasicBlock &MBB = *MBBI->getParent();
  MachineBasicBlock::iterator BeginMBBI = MBB.begin();
  MachineBasicBlock::iterator EndMBBI = MBB.end();
  if (MBBI == BeginMBBI)
    return EndMBBI;


  MachineBasicBlock::iterator PrevMBBI = std::prev(MBBI);
  while (PrevMBBI->isDebugValue() && PrevMBBI != BeginMBBI)
    --PrevMBBI;

  Offset = isIncrementOrDecrement(*PrevMBBI, Reg, Pred, PredReg);
  return Offset == 0 ? EndMBBI : PrevMBBI;
}
