FoldRestore(unsigned vreg,
                                             const TargetRegisterClass* RC,
                                             MachineInstr* Barrier,
                                             MachineBasicBlock* MBB,
                                             int SS,
                                     SmallPtrSet<MachineInstr*, 4>& RefsInMBB) {
  if ((int)RestoreFoldLimit != -1 && RestoreFoldLimit == (int)NumRestoreFolds)
    return 0;


  if (RefsInMBB.empty())
    return 0;


  MachineBasicBlock::iterator FoldPt = Barrier;


  while (FoldPt != MBB->getFirstTerminator() &&
         FoldPt->getOpcode() != TRI->getCallFrameDestroyOpcode()) {
    if (RefsInMBB.count(FoldPt))
      return 0;

    ++FoldPt;
  }

  if (FoldPt == MBB->getFirstTerminator())
    return 0;
  else
    ++FoldPt;


  while (FoldPt != MBB->getFirstTerminator() && !RefsInMBB.count(FoldPt)) {
    if (FoldPt->getOpcode() == TRI->getCallFrameSetupOpcode()) {
      while (FoldPt != MBB->getFirstTerminator() &&
             FoldPt->getOpcode() != TRI->getCallFrameDestroyOpcode()) {
        if (RefsInMBB.count(FoldPt))
          return 0;

        ++FoldPt;
      }

      if (FoldPt == MBB->getFirstTerminator())
        return 0;
    }

    ++FoldPt;
  }

  if (FoldPt == MBB->getFirstTerminator())
    return 0;

  int OpIdx = FoldPt->findRegisterUseOperandIdx(vreg, true);
  if (OpIdx == -1)
    return 0;

  SmallVector<unsigned, 1> Ops;
  Ops.push_back(OpIdx);

  if (!TII->canFoldMemoryOperand(FoldPt, Ops))
    return 0;

  MachineInstr* FMI = TII->foldMemoryOperand(FoldPt, Ops, SS);

  if (FMI) {
    LIs->ReplaceMachineInstrInMaps(FoldPt, FMI);
    FoldPt->eraseFromParent();
    ++NumRestoreFolds;
  }

  return FMI;
}
