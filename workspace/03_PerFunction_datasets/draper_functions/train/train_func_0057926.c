CreateSpillStackSlot(unsigned Reg,
                                            const TargetRegisterClass *RC) {
  int SS;
  DenseMap<unsigned, int>::iterator I = IntervalSSMap.find(Reg);
  if (I != IntervalSSMap.end()) {
    SS = I->second;
  } else {
    SS = MFI->CreateSpillStackObject(RC->getSize(), RC->getAlignment());
    IntervalSSMap[Reg] = SS;
  }


  CurrSLI = &LSs->getOrCreateInterval(SS, RC);
  if (CurrSLI->hasAtLeastOneValue())
    CurrSValNo = CurrSLI->getValNumInfo(0);
  else
    CurrSValNo = CurrSLI->getNextValue(SlotIndex(), 0, false,
                                       LSs->getVNInfoAllocator());
  return SS;
}
