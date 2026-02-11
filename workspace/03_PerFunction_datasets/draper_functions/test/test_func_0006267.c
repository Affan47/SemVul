RemoveBranch(MachineBasicBlock &MBB) const {
  MachineBasicBlock::iterator I = MBB.end();
  unsigned Count = 0;

  while (I != MBB.begin()) {
    --I;
    if (I->isDebugValue())
      continue;
    if (I->getOpcode() != BPF::JMP)
      break;

    I->eraseFromParent();
    I = MBB.end();
    ++Count;
  }

  return Count;
}
