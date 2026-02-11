needMigrateBlock(MachineBasicBlock *MBB) const {
  unsigned BlockSizeThreshold = 30;
  unsigned CloneInstrThreshold = 100;
  bool MultiplePreds = MBB && (MBB->pred_size() > 1);

  if(!MultiplePreds)
    return false;
  unsigned BlkSize = MBB->size();
  return ((BlkSize > BlockSizeThreshold) &&
      (BlkSize * (MBB->pred_size() - 1) > CloneInstrThreshold));
}
