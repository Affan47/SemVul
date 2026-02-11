ReplaceTailWithBranchTo(MachineBasicBlock::iterator Tail,
                                         MachineBasicBlock *NewDest) const {
  MachineBasicBlock *MBB = Tail->getParent();
  ARMFunctionInfo *AFI = MBB->getParent()->getInfo<ARMFunctionInfo>();
  if (!AFI->hasITBlocks()) {
    TargetInstrInfo::ReplaceTailWithBranchTo(Tail, NewDest);
    return;
  }


  unsigned PredReg = 0;
  ARMCC::CondCodes CC = getInstrPredicate(Tail, PredReg);
  MachineBasicBlock::iterator MBBI = Tail;
  if (CC != ARMCC::AL)

    --MBBI;


  TargetInstrInfo::ReplaceTailWithBranchTo(Tail, NewDest);


  if (CC != ARMCC::AL) {
    MachineBasicBlock::iterator E = MBB->begin();
    unsigned Count = 4;
    while (Count && MBBI != E) {
      if (MBBI->isDebugValue()) {
        --MBBI;
        continue;
      }
      if (MBBI->getOpcode() == ARM::t2IT) {
        unsigned Mask = MBBI->getOperand(1).getImm();
        if (Count == 4)
          MBBI->eraseFromParent();
        else {
          unsigned MaskOn = 1 << Count;
          unsigned MaskOff = ~(MaskOn - 1);
          MBBI->getOperand(1).setImm((Mask & MaskOff) | MaskOn);
        }
        return;
      }
      --MBBI;
      --Count;
    }


  }
}
