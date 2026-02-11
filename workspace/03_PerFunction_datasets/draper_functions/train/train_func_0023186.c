RemoveBranch(MachineBasicBlock &MBB) const {
  MachineBasicBlock::iterator I = MBB.end();
  unsigned Count = 0;

  while (I != MBB.begin()) {
    --I;
    if (I->isDebugValue())
      continue;
    if (I->getOpcode() != X86::JMP_4 &&
        GetCondFromBranchOpc(I->getOpcode()) == X86::COND_INVALID)
      break;

    I->eraseFromParent();
    I = MBB.end();
    ++Count;
  }

  return Count;
}
