EliminatePHINodes(MachineFunction &MF,
                                             MachineBasicBlock &MBB) {
  if (MBB.empty() || !MBB.front().isPHI())
    return false;


  MachineBasicBlock::iterator LastPHIIt =
    std::prev(MBB.SkipPHIsAndLabels(MBB.begin()));

  while (MBB.front().isPHI())
    LowerPHINode(MBB, LastPHIIt);

  return true;
}
