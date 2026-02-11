addDummyExitBlock(
    SmallVectorImpl<MachineBasicBlock*> &RetMBB) {
  MachineBasicBlock *DummyExitBlk = FuncRep->CreateMachineBasicBlock();
  FuncRep->push_back(DummyExitBlk);
  insertInstrEnd(DummyExitBlk, AMDGPU::RETURN);

  for (SmallVectorImpl<MachineBasicBlock *>::iterator It = RetMBB.begin(),
       E = RetMBB.end(); It != E; ++It) {
    MachineBasicBlock *MBB = *It;
    MachineInstr *MI = getReturnInstr(MBB);
    if (MI)
      MI->eraseFromParent();
    MBB->addSuccessor(DummyExitBlk);
    DEBUG(
      dbgs() << "Add dummyExitBlock to BB" << MBB->getNumber()
             << " successors\n";
    );
  }
  SHOWNEWBLK(DummyExitBlk, "DummyExitBlock: ");
}
