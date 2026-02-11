FoldSpill(unsigned vreg,
                                           const TargetRegisterClass* RC,
                                           MachineInstr* DefMI,
                                           MachineInstr* Barrier,
                                           MachineBasicBlock* MBB,
                                           int& SS,
                                    SmallPtrSet<MachineInstr*, 4>& RefsInMBB) {

  if (RefsInMBB.empty())
    return 0;

  MachineBasicBlock::iterator FoldPt = Barrier;
  while (&*FoldPt != DefMI && FoldPt != MBB->begin() &&
         !RefsInMBB.count(FoldPt))
    --FoldPt;

  int OpIdx = FoldPt->findRegisterDefOperandIdx(vreg);
  if (OpIdx == -1)
    return 0;

  SmallVector<unsigned, 1> Ops;
  Ops.push_back(OpIdx);

  if (!TII->canFoldMemoryOperand(FoldPt, Ops))
    return 0;

  DenseMap<unsigned, int>::iterator I = IntervalSSMap.find(vreg);
  if (I != IntervalSSMap.end()) {
    SS = I->second;
  } else {
    SS = MFI->CreateSpillStackObject(RC->getSize(), RC->getAlignment());
  }

  MachineInstr* FMI = TII->foldMemoryOperand(FoldPt, Ops, SS);

  if (FMI) {
    LIs->ReplaceMachineInstrInMaps(FoldPt, FMI);
    FoldPt->eraseFromParent();
    ++NumFolds;

    IntervalSSMap[vreg] = SS;
    CurrSLI = &LSs->getOrCreateInterval(SS, RC);
    if (CurrSLI->hasAtLeastOneValue())
      CurrSValNo = CurrSLI->getValNumInfo(0);
    else
      CurrSValNo = CurrSLI->getNextValue(SlotIndex(), 0, false,
                                         LSs->getVNInfoAllocator());
  }

  return FMI;
}
