RemoveBranch(MachineBasicBlock &MBB) const {
  MachineBasicBlock::iterator I = MBB.end();
  if (I == MBB.begin())
    return 0;
  --I;
  if (I->getOpcode() != NVPTX::GOTO && I->getOpcode() != NVPTX::CBranch)
    return 0;


  I->eraseFromParent();

  I = MBB.end();

  if (I == MBB.begin())
    return 1;
  --I;
  if (I->getOpcode() != NVPTX::CBranch)
    return 1;


  I->eraseFromParent();
  return 2;
}
