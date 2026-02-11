addNodeToList(MachineBasicBlock *N) {
  MachineFunction &MF = *N->getParent();
  N->Number = MF.addToMBBNumbering(N);


  MachineRegisterInfo &RegInfo = MF.getRegInfo();
  for (MachineBasicBlock::iterator I = N->begin(), E = N->end(); I != E; ++I)
    I->AddRegOperandsToUseLists(RegInfo);

  LeakDetector::removeGarbageObject(N);
}
